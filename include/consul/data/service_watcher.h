#ifndef RTCFG_SERVICE_WATCHER_H
#define RTCFG_SERVICE_WATCHER_H

#include <utility>

#include "defines.h"
#include "consul/data/data_watcher.h"

namespace rtcfg::consul {
    class ConsulServiceWatcher : public ConsulDataWatcher {
        String service_;
        long data_index_{0};
    public:
        ConsulServiceWatcher(ConsulClient &consul, String service) :
                ConsulDataWatcher(consul), service_(MOVE(service)) {}

        void DoWatch() override;
    };

    typedef std::shared_ptr<ConsulServiceWatcher> ConsulServiceWatcherPtr;
}

#endif //RTCFG_SERVICE_WATCHER_H
