#include "consul/kv/kv_watcher.h"
#include "exceptions.h"

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
        SSMap params{{"index", std::to_string(data_index_)}};
        try {
            auto rsp = consul_.GetKV(path_, params);
            auto result = ConsulKVGroup{};
            data_index_ = rsp.first;
            auto j = nlohmann::json::parse(rsp.second);
            for (auto &e: j) {
                spdlog::info("[KVWatcher]-DoWatch: parse kv. [data={}]", e.dump());
                auto r = std::make_shared<ConsulKV>(e);
                result.emplace(r->key, r);
            }
            spdlog::debug("[ConsulKVWatcher]-DoWatch: swap data. [before={}, after={}]", data_.size(), result.size());
            std::swap(data_, result);
            result.clear();
        } catch (ReadTimeoutException &err) { // ignore long pulling timeout error
            spdlog::debug("[ConsulKVWatcher]-DoWatch: read timeout. [message={}]", err.what());
        }
    }
}