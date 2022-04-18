#ifndef RTCFG_THREAD_H
#define RTCFG_THREAD_H

#include <csignal>
#include "defines.h"

#define CUSTOM_STOP_SIGNAL SIGUSR1;

namespace rtcfg {
    typedef void *(*ThreadFn)(void *);

    class Thread {
        pthread_t thread_{};
        String name_;
        ThreadFn fn_{};
        void *data_{};
        bool start_{false};
        Thread() = default;

        static void empty_signal_handler(int signum) {};
        static struct sigaction old_action;
    public:
        Thread(const String &name, ThreadFn fn, void *data = nullptr) : name_(name), fn_(fn), data_(data) {}
        static void Init();
        static void Reset();
        void Start();
        void Join();
        void Kill();
        void SetThreadName(const String &name);
        String GetThreadName();
    };
}

#endif //RTCFG_THREAD_H
