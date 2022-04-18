#include "thread/thread.h"

namespace rtcfg {
    void Thread::Init() {
        struct sigaction action{};
        action.sa_flags = 0;
        action.sa_handler = empty_signal_handler;
        sigemptyset(&action.sa_mask);
        sigaction(CUSTOM_STOP_SIGNAL, &old_action, nullptr);
    }

    void Thread::Reset() {
        sigaction(CUSTOM_STOP_SIGNAL, &old_action, nullptr);
    }

    void Thread::Run(void *param) {
        auto *cur = (Thread *) param;
        pthread_threadid_np(nullptr, &cur->tid_);
    }

    void Thread::Start() {

    }
}