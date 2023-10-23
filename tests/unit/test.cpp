#include "rtcfg.h"
#include "spdlog/spdlog.h"

using namespace rtcfg;

int main() {
    spdlog::set_level(spdlog::level::debug);
    SSMap properties{};
    consul::Consul cs = RTCFG::GetConsul(properties);
    auto &kv = cs.GetKVService();
    String key = "foo";
    spdlog::info("key: {}, value: {}", key, kv.Get(key));
    auto watcher = kv.Cache(key);
    watcher->Start();

    // service
    auto &srv = cs.GetNamingService();
    auto srv_res = srv.Get("consul");
    spdlog::info("{}", srv_res);
    auto srv_cache = srv.Cache("consul");
    srv_cache->Start();

    // done
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}