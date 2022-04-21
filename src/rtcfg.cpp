#include "rtcfg.h"
#include "exceptions.h"
#include "consul/service/kv_service.h"

namespace rtcfg {
    consul::ConsulKVService RTCFG::GetConsulKVService(const SSMap &config) {
        return consul::ConsulKVService(config);
    }
}