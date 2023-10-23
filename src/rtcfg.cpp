#include "rtcfg.h"
#include "exceptions.h"
#include "consul/consul.h"

namespace rtcfg {
    consul::Consul RTCFG::GetConsul(const SSMap &config) {
        return consul::Consul(config);
    }
}