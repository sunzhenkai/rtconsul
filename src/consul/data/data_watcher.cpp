#include "consul/data/data_watcher.h"
#include "exceptions.h"

namespace rtcfg::consul {
    template<typename V>
    VPtr<V> ConsulDataWatcher<V>::GetData() {
        return data_;
    }

    template<typename V>
    void *ConsulDataWatcher<V>::Run(void *param) {
        auto *w = (ConsulDataWatcher<V> *) param;
        while (w->started_) {
            w->DoWatch();
        }
        return nullptr;
    }

    template<typename V>
    void ConsulDataWatcher<V>::Start() {
        pthread_mutex_lock(&thread_mutex_);
        if (!started_) {
            pthread_create(&tid_, nullptr, ConsulDataWatcher<V>::Run, (void *) this);
            started_ = true;
        }
        pthread_mutex_unlock(&thread_mutex_);
    }

    template<typename V>
    void ConsulDataWatcher<V>::Stop() {
        pthread_mutex_lock(&thread_mutex_);
        if (started_) {
            pthread_join(tid_, nullptr);
            started_ = false;
        }
        pthread_mutex_unlock(&thread_mutex_);
    }
}