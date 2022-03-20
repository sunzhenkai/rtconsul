#ifndef RTCFG_FACTORY_IFACE_H
#define RTCFG_FACTORY_IFACE_H

#include "service/kv_service.h"
#include "service/naming_service.h"

namespace rtcfg {
    class FactoryIFace {
        virtual KVService GetKVService();

        virtual NamingService GetNamingService();
    };
}

#endif //RTCFG_FACTORY_IFACE_H
