#ifndef RTCFG_NAMING_SERVICE_H
#define RTCFG_NAMING_SERVICE_H

#include "consul/client/consul_client.h"
#include "consul/data/service_watcher.h"
#include "utils/safe_map.h"


namespace rtcfg::consul {
    class ConsulNamingService {
        ConsulClient &consul_client_;
        SafeMap<String, ConsulServiceWatcherPtr> caches;
    public:
        explicit ConsulNamingService(ConsulClient &consul) : consul_client_(consul) {}
        String Get(const String &service, const SSMap &params = EMPTY_SS_MAP);
    };
}


#endif //RTCFG_NAMING_SERVICE_H
