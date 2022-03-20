#ifndef RTCFG_FACTORY_H
#define RTCFG_FACTORY_H

#include "factory/factory_iface.h"
#include "constants/common.h"

namespace rtcfg {
    class Factory {
        FactoryIFace GetFactory(Properties props);
    };
}

#endif //RTCFG_FACTORY_H
