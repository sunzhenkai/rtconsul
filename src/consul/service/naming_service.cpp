#include "consul/service/naming_service.h"

namespace rtcfg::consul {
    String ConsulNamingService::Get(const String &service, const SSMap &params) {
        return consul_client_.GetHealthService(service, params).second;
    }
}