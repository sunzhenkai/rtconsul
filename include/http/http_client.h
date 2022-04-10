#ifndef RTCFG_HTTP_CLIENT_H
#define RTCFG_HTTP_CLIENT_H

#include "pthread.h"
#include "curl/curl.h"
#include "defines.h"
#include "http/http_result.h"
#include "utils/url.h"

namespace rtcfg {
    class HTTPClient {
        pthread_key_t pthread_key_{};
    public:
        HTTPClient();

        CURL *GetCurlHandler() const;

        HTTPResult Get(const String &path, SSMap &headers, SSMap &params, long timeout);

        static void DestroyCurlHandler(void *arg);

        static void InitCurl();

        static void CleanUp();

        static String EncodingParams(SSMap &params);

        static SList AssembleHeaders(SSMap &headers);

        static void SetBasicOpts(CURL *curl_handler);
    };
}

#endif //RTCFG_HTTP_CLIENT_H
