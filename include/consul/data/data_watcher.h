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
    class ConsulDataWatcher {
        pthread_t tid_{0};
        bool started_{false};
        pthread_mutex_t thread_mutex_{};
        int period_ms;
    protected:
        // consul
        ConsulClient &consul_;
    public:
        explicit ConsulDataWatcher(ConsulClient &consul, int period = 3000) : consul_(consul), period_ms(period) {}
        static void *Run(void *param);
        void Start();
        void Stop();
        void Join();
        virtual void DoWatch() = 0;
        ~ConsulDataWatcher() {
            Stop();
        }
    };
}

#endif //RTCFG_DATA_WATCHER_H
