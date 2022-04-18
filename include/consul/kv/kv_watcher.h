#ifndef RTCFG_KV_WATCHER_H
#define RTCFG_KV_WATCHER_H

#include "consul/kv/data_watcher.h"
#include "consul/model/consul_kv.h"

namespace rtcfg::consul {
    class ConsulKVWatcher : public DataWatcher<ConsulKVGroup> {
    public:
        ConsulKVWatcher(String key, DataWatcherFun<ConsulKVGroup> &&f) :
                DataWatcher<ConsulKVGroup>(std::move(key), std::move(f)) {
        }

        ConsulKV Get(const String &key) {
            ConsulKV kv;
            data.find(key);
            return std::move(kv);
        }
    };

    using ConsulKVWatcherPtr = std::shared_ptr<ConsulKVWatcher>;
}

#endif //RTCFG_KV_WATCHER_H
