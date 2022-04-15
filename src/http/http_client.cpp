#include "http/http_client.h"
#include "curl/curl.h"
#include "cstring"
#include "spdlog/spdlog.h"
#include "exceptions.h"

namespace rtcfg {
    static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *user_data) {
        size_t bts = size * nmemb;
        auto *r = (HTTPResult *) user_data;
        r->content.append((char *) ptr, bts);
        return bts;
    }

    static size_t ReadHeaderCallback(void *ptr, size_t size, size_t nmemb, void *user_data) {
        char *content = (char *) ptr;
        char *pos = strchr(content, ':');
        if (pos != nullptr) { // ignore status
            auto *r = (HTTPResult *) user_data;
            r->headers.emplace(String(content, pos - content), String(pos + 1));
        }
        return size * nmemb;
    }

    HTTPClient::HTTPClient() {
        pthread_key_create(&pthread_key_, HTTPClient::DestroyCurlHandler);
    }

    SSMap HTTPClient::EMPTY_MAP{};

    void HTTPClient::DestroyCurlHandler(void *arg) {
        CURL *curl_handler = reinterpret_cast<CURL *>(arg);
        if (curl_handler != nullptr) {
            curl_easy_cleanup(curl_handler);
            curl_handler = nullptr;
        }
    }

    CURL *HTTPClient::GetCurlHandler() const {
        CURL *curl_handler = pthread_getspecific(pthread_key_);
        if (curl_handler == nullptr) {
            curl_handler = curl_easy_init();
            pthread_setspecific(pthread_key_, reinterpret_cast<void *>(curl_handler));
        }
        return curl_handler;
    }

    HTTPResult HTTPClient::Get(const String &path, SSMap &headers, SSMap &params, long timeout) {
        CURL *curl_handler = GetCurlHandler();
        CURLcode curl_res;
        String url = path;

        String params_encoded = EncodingParams(params);
        if (!params_encoded.empty()) {
            url.append("?").append(url);
        }

        SList assembled_headers = AssembleHeaders(headers);
        curl_easy_reset(curl_handler);
        spdlog::debug("[HTTPClient]-Get: url. [url={}]", url);
        curl_easy_setopt(curl_handler, CURLOPT_URL, url.c_str());

        HTTPResult r;
        SetBasicOpts(curl_handler);

        curl_easy_setopt(curl_handler, CURLOPT_TIMEOUT_MS, timeout);
        curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, (void *) &r);
        curl_easy_setopt(curl_handler, CURLOPT_HEADERDATA, (void *) &r);

        struct curl_slist *header_list = nullptr;
        for (auto &it: assembled_headers) {
            header_list = curl_slist_append(header_list, it.c_str());
        }
        if (header_list != nullptr) {
            curl_easy_setopt(curl_handler, CURLOPT_HEADER, header_list);
        }

        curl_res = curl_easy_perform(curl_handler);
        if (header_list != nullptr) {
            curl_slist_free_all(header_list);
        }

        if (curl_res != CURLE_OK) {
            spdlog::error("[HTTPClient]-Get:curl_easy_perform() failed: {} - {}",
                          curl_res, curl_easy_strerror(curl_res));
            throw NetworkException(curl_res, curl_easy_strerror(curl_res));
        }

        curl_easy_getinfo(curl_handler, CURLINFO_RESPONSE_CODE, &r.code);
        return r;
    }

    void HTTPClient::InitCurl() {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    void HTTPClient::CleanUp() {
        curl_global_cleanup();
    }

    String HTTPClient::EncodingParams(SSMap &params) {
        String result;
        for (const auto &it: params) {
            if (!result.empty()) {
                result.append("&");
            }
            result.append(URLEncode(it.first));
            result.append("=");
            result.append(URLEncode(it.second));
        }
        return result;
    }

    SList HTTPClient::AssembleHeaders(SSMap &headers) {
        SList result;
        for (const auto &it: headers) {
            result.emplace_back(it.first + ": " + it.second);
        }
        return result;
    }

    void HTTPClient::SetBasicOpts(CURL *curl_handler) {
        curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_handler, CURLOPT_HEADERFUNCTION, ReadHeaderCallback);
        curl_easy_setopt(curl_handler, CURLOPT_TCP_KEEPALIVE, 1L);
        /* keep-alive idle time to 120 seconds */
        curl_easy_setopt(curl_handler, CURLOPT_TCP_KEEPIDLE, 120L);
        /* interval time between keep-alive probes: 60 seconds */
        curl_easy_setopt(curl_handler, CURLOPT_TCP_KEEPINTVL, 60L);
    }
}