#ifndef RTCFG_KV_WATCHER_H
#define RTCFG_KV_WATCHER_H

#include <thread>
#include <atomic>
#include "consul/model/consul_kv.h"

namespace rtcfg::consul {
    class ConsulKVWatcher {
        pthread_t tid_{0};
        bool started_{false};
        String path_;
        Map<String, ConsulKVPtr> data_;
        pthread_mutex_t thread_mutex_;
    public:
        explicit ConsulKVWatcher(String path) : path_(std::move(path)) {}

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
