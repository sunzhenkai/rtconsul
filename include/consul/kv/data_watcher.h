#ifndef RTCFG_DATA_WATCHER_H
#define RTCFG_DATA_WATCHER_H

#include <thread>
#include <functional>
#include <csignal>
#include "thread/thread.h"

namespace rtcfg::consul {
    template<typename T>
    using DataWatcherFun = std::function<T()>;

    template<typename T>
    class DataWatcher {
    protected:
        String key_;
        std::thread trd;
        pthread_t thread_native_handler;
        T data;
    public:
        DataWatcher(String key, DataWatcherFun<T> &&f) : trd(f, data), key_(std::move(key)) {
            thread_native_handler = trd.native_handle();
        }

        String GetKey() {
            return key_;
        }

        T &GetData() {
            return data;
        }

        ~DataWatcher() {
            // TODO not work
            pthread_kill(thread_native_handler, SIGUSR1);
        }
    };

    template<typename T>
    using DataWatcherPtr = std::shared_ptr<DataWatcher<T>>;
}

#endif //RTCFG_DATA_WATCHER_H
