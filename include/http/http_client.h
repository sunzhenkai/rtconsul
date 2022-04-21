#ifndef RTCFG_HTTP_CLIENT_H
#define RTCFG_HTTP_CLIENT_H

#include "pthread.h"
#include "curl/curl.h"
#include "defines.h"
#include "http/http_result.h"
#include "utils/url.h"

namespace rtcfg {
    class HTTPClient {
        static SSMap EMPTY_MAP;
        pthread_key_t pthread_key_{};
    public:
        HTTPClient();
        HTTPResult
        Get(const String &path, const SSMap &params = EMPTY_MAP, const SSMap &headers = EMPTY_MAP, long timeout = 5000);
        static void InitCurl();
        static void CleanUp();
    private:
        CURL *GetCurlHandler() const;
        static void DestroyCurlHandler(void *arg);
        static String EncodingParams(const SSMap &params);
        static SList AssembleHeaders(const SSMap &headers);
        static void SetBasicOpts(CURL *curl_handler);
    };
}

#endif //RTCFG_HTTP_CLIENT_H
