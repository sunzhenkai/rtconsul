#include "consul/data/data_watcher.h"
#include "exceptions.h"

namespace rtcfg::consul {
    VPtr DataWatcher::Get(const String &key) {
        auto it = data_.find(key);
        return it == data_.end() ? std::shared_ptr<V>(nullptr) : it->second;
    }

    void *ConsulServiceWatcher::Run(void *param) {
        auto *w = (ConsulServiceWatcher *) param;
        while (w->started_) {
            w->DoWatch();
        }
        return nullptr;
    }

    void ConsulServiceWatcher::Start() {
        pthread_mutex_lock(&thread_mutex_);
        if (!started_) {
            pthread_create(&tid_, nullptr, ConsulServiceWatcher::Run, (void *) this);
            started_ = true;
        }
        pthread_mutex_unlock(&thread_mutex_);
    }

    void ConsulServiceWatcher::Stop() {
        pthread_mutex_lock(&thread_mutex_);
        if (started_) {
            pthread_join(tid_, nullptr);
            started_ = false;
        }
        pthread_mutex_unlock(&thread_mutex_);
    }

    void ConsulServiceWatcher::DoWatch() {
        SSMap params{{"index", std::to_string(data_index_)}};
        try {
            auto rsp = consul_.GetKV(path_, params);
            auto result = ConsulServicesGroup{};
            data_index_ = rsp.first;
            auto j = nlohmann::json::parse(rsp.second);
            for (auto &e: j) {
                spdlog::info("[KVWatcher]-DoWatch: parse kv. [data={}]", e.dump());
                auto r = std::make_shared<V>(e);
                result.emplace(r->key, r);
            }
            spdlog::debug("[ConsulServiceWatcher]-DoWatch: swap data. [before={}, after={}]", data_.size(),
                          result.size());
            std::swap(data_, result);
            result.clear();
        } catch (ReadTimeoutException &err) { // ignore long pulling timeout error
            spdlog::debug("[ConsulServiceWatcher]-DoWatch: read timeout. [message={}]", err.what());
        }
    }
}