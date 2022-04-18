#include "rtcfg.h"
#include "spdlog/spdlog.h"

using namespace rtcfg;

int main() {
    spdlog::set_level(spdlog::level::debug);
    SSMap properties{
            {"protocol", "consul"},
    };
    consul::ConsulKVService cs = RTCFG::GetConsulKVService(properties);
    String key = "foo";
    spdlog::info("key: {}, value: {}", key, cs.Get(key));
    auto watcher = cs.Cache(key);
    spdlog::info("key: {}, data: {}", watcher->GetKey(), watcher->GetData().Size());
    return 0;
}