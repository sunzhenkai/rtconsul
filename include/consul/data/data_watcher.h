#ifndef RTCFG_DATA_WATCHER_H
#define RTCFG_DATA_WATCHER_H

#include <thread>
#include <atomic>
#include <utility>
#include "nlohmann/json.hpp"
#include "consul/model/consul_service.h"
#include "consul/client/consul_client.h"
#include "defines.h"

namespace rtcfg::consul {
    template<typename V>
    using VPtr = std::shared_ptr<V>;

    template<typename V>
    class ConsulDataWatcher {
        pthread_t tid_{0};
        bool started_{false};
        pthread_mutex_t thread_mutex_{};
        // consul
        ConsulClient &consul_;
        String path_;
        long data_index_{};
        // data
        VPtr<V> data_;
    public:
        ConsulDataWatcher(ConsulClient &consul, String path) : consul_(consul), path_(MOVE(path)) {}
        VPtr<V> GetData();
        static void *Run(void *param);
        void Start();
        void Stop();
        virtual void DoWatch() = 0;
        ~ConsulDataWatcher() {
            Stop();
        }
    };

    template<typename V>
    using ConsulDataWatcherPtr = std::shared_ptr<ConsulDataWatcher<V>>;
}

#endif //RTCFG_DATA_WATCHER_H
