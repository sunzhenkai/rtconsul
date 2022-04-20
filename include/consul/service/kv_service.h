#ifndef RTCFG_KV_SERVICE_H
#define RTCFG_KV_SERVICE_H

#include "defines.h"
#include "listener/listener.h"
#include "service/config_service.h"
#include "consul/client/consul_client.h"
#include "consul/kv/kv_watcher.h"
#include "consul/model/consul_kv.h"
#include "utils/safe_map.h"

namespace rtcfg::consul {
    class ConsulKVService : public ConfigService<ConsulKVWatcherPtr> {
    private:
        ConsulClient consul;
        SafeMap<String, ConsulKVWatcherPtr> caches;
    public:
        explicit ConsulKVService(const SSMap &props) : consul(props) {}
        String Get(const String &key) override;
        ConsulKVWatcherPtr Cache(const String &key) override;
        void DiscardCache(const String &key) override;
        void Subscribe(const String &key, Listener *listener) override;
        void Unsubscribe(const String &key, Listener *listener) override;
    };
}

#endif //RTCFG_KV_SERVICE_H
