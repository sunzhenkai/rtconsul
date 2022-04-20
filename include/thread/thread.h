#ifndef RTCFG_THREAD_H
#define RTCFG_THREAD_H

#include <thread>
#include "defines.h"

namespace rtcfg {
    class LoopThread {
        String name_;
        std::thread thread_;
        bool started_{false};
    public:
        LoopThread(String name) : name_(std::move(name)) {

        }
    };
}


#endif //RTCFG_THREAD_H
