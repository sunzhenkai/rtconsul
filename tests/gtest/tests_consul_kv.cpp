#include "gtest/gtest.h"
#include "rtcfg.h"

TEST(ConsulKv, Read) {
    rtcfg::SSMap properties{
            {"host", "http://127.0.0.1:8500"}
    };
    rtcfg::consul::Consul cs = rtcfg::RTCFG::GetConsul(properties);
    auto &kv = cs.GetKVService();
    std::string key = "foo";
    spdlog::info("key: {}, value: {}", key, kv.Get(key));
    auto watcher = kv.Cache(key);
    auto v = watcher->Get(key);
    if (v) {
        spdlog::info("value: {}", v->value);
    }
}