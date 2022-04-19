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

    void *Thread::Run(void *param) {
        auto *cur = (Thread *) param;
        cur->tid_ = pthread_self();
        try {
            return cur->fn_(cur->data_);
        } catch (...) {
            cur->fn_ = nullptr;
            abort();
        }
    }

    void Thread::Start() {
        if (!start_.exchange(true)) {
            pthread_create(&thread_, nullptr, Run, (void *) this);
        }
    }

    void Thread::Join() {
        if (start_) {
            pthread_join(thread_, nullptr);
        }
    }

    void Thread::Kill() {
        pthread_kill(thread_, CUSTOM_STOP_SIGNAL);
    }

    String Thread::GetThreadName() {
        return name_;
    }
}