#include "utils/url.h"

namespace rtcfg {
    String URLEncode(const String &data) {
        String result;
        CURL *curl = curl_easy_init();
        char *output = nullptr;
        if (curl) {
            output = curl_easy_escape(curl, data.c_str(), data.length());
        }
        if (output) {
            result = output;
            curl_free(output);
        }
        curl_easy_cleanup(curl);
        return result;
    }

    String URLDecode(const String &data) {
        String result;
        CURL *curl = curl_easy_init();
        char *output = nullptr;
        if (curl) {
            output = curl_easy_unescape(curl, data.c_str(), data.length(), nullptr);
        }
        if (output) {
            result = output;
            curl_free(output);
        }
        curl_easy_cleanup(curl);
        return result;
    }
}