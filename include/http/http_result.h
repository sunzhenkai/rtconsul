#ifndef RTCFG_HTTP_RESULT_H
#define RTCFG_HTTP_RESULT_H

#include "defines.h"

namespace rtcfg {
    class HTTPResult {
    public:
        long code;
        String content;
        SSMap headers;
    };
}


#endif //RTCFG_HTTP_RESULT_H
