#ifndef RTCFG_RTCFG_FACTORY_H
#define RTCFG_RTCFG_FACTORY_H

#include "service/config_service.h"
#include "defines.h"

namespace rtcfg {
    class RTCFG {
    public:
        static ConfigServicePtr GetConfigService(const SSMap &config);
    };
}

#endif //RTCFG_RTCFG_FACTORY_H
