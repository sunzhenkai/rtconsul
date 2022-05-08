#ifndef RTCFG_SERVICE_WATCHER_H
#define RTCFG_SERVICE_WATCHER_H

#include "defines.h"
#include "consul/data/data_watcher.h"

namespace rtcfg::consul {
    class ConsulServiceWatcher : public ConsulDataWatcher<String> {
    public:
        ConsulServiceWatcher(ConsulClient &consul, String path) : ConsulDataWatcher<String>(consul, path) {
        }

        void DoWatch() override;
    };

    typedef std::shared_ptr<ConsulServiceWatcher> ConsulServiceWatcherPtr;
}

#endif //RTCFG_SERVICE_WATCHER_H
