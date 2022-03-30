#include "init.h"
#include "http/http_client.h"

namespace rtcfg {
    void Init::DoInit() {
        HTTPClient::InitCurl();
    }
}