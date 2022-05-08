#ifndef RTCFG_RTCFG_FACTORY_H
#define RTCFG_RTCFG_FACTORY_H

#include "service/config_service.h"
#include "defines.h"
#include "consul/consul.h"

namespace rtcfg {
    class RTCFG {
    public:
        static consul::Consul GetConsul(const SSMap &config);
    };
}

#endif //RTCFG_RTCFG_FACTORY_H
