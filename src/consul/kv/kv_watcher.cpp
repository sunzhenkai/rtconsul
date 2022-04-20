#include "consul/kv/kv_watcher.h"

namespace rtcfg::consul {
    ConsulKVPtr ConsulKVWatcher::Get(const String &key) {
        auto it = data_.find(key);
        return it == data_.end() ? std::shared_ptr<ConsulKV>(nullptr) : it->second;
    }

    void *ConsulKVWatcher::Run(void *param) {
        auto *w = (ConsulKVWatcher *) param;
        while (w->started_) {
            w->DoWatch();
        }
        return nullptr;
    }

    void ConsulKVWatcher::Start() {
        pthread_mutex_lock(&thread_mutex_);
        if (!started_) {
            pthread_create(&tid_, nullptr, ConsulKVWatcher::Run, (void *) this);
            started_ = true;
        }
        pthread_mutex_unlock(&thread_mutex_);
    }

    void ConsulKVWatcher::Stop() {
        pthread_mutex_lock(&thread_mutex_);
        if (started_) {
            pthread_join(tid_, nullptr);
            started_ = false;
        }
        pthread_mutex_unlock(&thread_mutex_);
    }

    void ConsulKVWatcher::DoWatch() {
        // TODO
        auto f = [&]() -> ConsulKVGroup {
            auto result = ConsulKVGroup{};
            auto rsp = consul.GetKV(key);
            auto j = nlohmann::json::parse(rsp);
            for (auto &e: j) {
                result[key] = ConsulKV(e);
            }
            return std::move(result);
        };
    }
}