#ifndef RTCFG_KV_SERVICE_H
#define RTCFG_KV_SERVICE_H

#include "defines.h"
#include "listener/listener.h"
#include "service/config_service.h"
#include "consul/client/consul_client.h"
#include "consul/data/kv_watcher.h"
#include "consul/model/consul_kv.h"
#include "utils/safe_map.h"

namespace rtcfg::consul {
    /**
     * Consul Kv watcher manager.
     */
    class ConsulKVService {
    private:
        ConsulClient &consul_client_;
        SafeMap<String, ConsulKVWatcherPtr> caches;
    public:
        explicit ConsulKVService(ConsulClient &consul) : consul_client_(consul) {}
        // get data from key-prefix
        String Get(const String &key, const SSMap &params = EMPTY_SS_MAP);
        // cache key-prefix data, return watcher
        ConsulKVWatcherPtr Cache(const String &key);
        void DiscardCache(const String &key);
        void Subscribe(const String &key, Listener *listener);
        void Unsubscribe(const String &key, Listener *listener);
    };
}


#endif //RTCFG_KV_SERVICE_H
