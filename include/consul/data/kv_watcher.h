#ifndef RTCFG_KV_WATCHER_H
#define RTCFG_KV_WATCHER_H

#include <thread>
#include <atomic>
#include <utility>
#include "consul/model/consul_kv.h"
#include "consul/client/consul_client.h"
#include "defines.h"

namespace rtcfg::consul {
    class ConsulKVWatcher {
        ConsulClient &consul_;
        pthread_t tid_{0};
        bool started_{false};
        String path_;
        Map<String, ConsulKVPtr> data_;
        pthread_mutex_t thread_mutex_{};
        long data_index_{};
    public:
        ConsulKVWatcher(ConsulClient &consul, String path) : consul_(consul), path_(MOVE(path)) {}
        ConsulKVPtr Get(const String &key);
        static void *Run(void *param);
        void Start();
        void Stop();
        void DoWatch();
        ~ConsulKVWatcher() {
            Stop();
        }
    };

    using ConsulKVWatcherPtr = std::shared_ptr<ConsulKVWatcher>;
}

#endif //RTCFG_KV_WATCHER_H
