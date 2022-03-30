#include "http/http_client.h"
#include "curl/curl.h"

namespace rtcfg {
    HTTPClient::HTTPClient() {
        pthread_key_create(&pthread_key_, HTTPClient::DestroyCurlHandler);
    }

    void HTTPClient::DestroyCurlHandler(void *arg) {
        CURL *curl_handler = reinterpret_cast<CURL *>(arg);
        if (curl_handler != nullptr) {
            curl_easy_cleanup(curl_handler);
            curl_handler = nullptr;
        }
    }

    CURL *HTTPClient::GetCurlHandler() {
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
        curl_easy_setopt(curl_handler, CURLOPT_URL, url.c_str());
        SetBasicOpts(curl_handler);

        // TODO here
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
        curl_easy_setopt(curl_handler, CURLOPT_TCP_KEEPALIVE, 1L);

        /* keep-alive idle time to 120 seconds */
        curl_easy_setopt(curl_handler, CURLOPT_TCP_KEEPIDLE, 120L);

        /* interval time between keep-alive probes: 60 seconds */
        curl_easy_setopt(curl_handler, CURLOPT_TCP_KEEPINTVL, 60L);
    }
}