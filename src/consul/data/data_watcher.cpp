#include "consul/data/data_watcher.h"
#include "exceptions.h"

namespace rtcfg::consul {
    void *ConsulDataWatcher::Run(void *param) {
        auto *w = (ConsulDataWatcher *) param;
        while (w->started_) {
            w->DoWatch();
        }
        return nullptr;
    }

    void ConsulDataWatcher::Start() {
        pthread_mutex_lock(&thread_mutex_);
        if (!started_) {
            pthread_create(&tid_, nullptr, ConsulDataWatcher::Run, (void *) this);
            started_ = true;
        }
        pthread_mutex_unlock(&thread_mutex_);
    }

    void ConsulDataWatcher::Stop() {
        pthread_mutex_lock(&thread_mutex_);
        if (started_) {
            pthread_join(tid_, nullptr);
            started_ = false;
        }
        pthread_mutex_unlock(&thread_mutex_);
    }
}