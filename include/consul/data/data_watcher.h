#ifndef RTCFG_SERVICE_WATCHER_H
#define RTCFG_SERVICE_WATCHER_H

#include <thread>
#include <atomic>
#include <utility>
#include "consul/model/consul_service.h"
#include "consul/client/consul_client.h"
#include "defines.h"

namespace rtcfg::consul {
    template<typename V>
    class ConsulDataWatcher {
        using VPtr = std::shared_ptr<V>;

        ConsulClient &consul_;
        pthread_t tid_{0};
        bool started_{false};
        String path_;
        Map<String, V> data_;
        pthread_mutex_t thread_mutex_{};
        long data_index_;
    public:
        ConsulDataWatcher(ConsulClient &consul, String path) : consul_(consul), path_(MOVE(path)) {}

        VPtr Get(const String &key);

        static void *Run(void *param);

        void Start();

        void Stop();

        void DoWatch();

        ~ConsulDataWatcher() {
            Stop();
        }
    };

    using ConsulDataWatcherPtr = std::shared_ptr<ConsulDataWatcher>;
}

#endif //RTCFG_SERVICE_WATCHER_H
