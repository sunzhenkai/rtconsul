#ifndef RTCFG_RTCFG_FACTORY_H
#define RTCFG_RTCFG_FACTORY_H

#include "service/config_service.h"
#include "defines.h"
#include "consul/service/kv_service.h"

namespace rtcfg {
    class RTCFG {
    public:
        static consul::ConsulKVService GetConsulKVService(const SSMap &config);
    };
}

#endif //RTCFG_RTCFG_FACTORY_H
