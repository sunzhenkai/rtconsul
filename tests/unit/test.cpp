#include "rtcfg.h"
#include "spdlog/spdlog.h"

using namespace rtcfg;

int main() {
    spdlog::set_level(spdlog::level::debug);
    SSMap properties{};
    consul::ConsulKVService cs = RTCFG::GetConsulKVService(properties);
    String key = "foo";
    spdlog::info("key: {}, value: {}", key, cs.Get(key));
    auto watcher = cs.Cache(key);
    watcher->Start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}