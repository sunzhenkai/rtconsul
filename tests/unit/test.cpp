#include "rtcfg.h"
#include "spdlog/spdlog.h"

using namespace rtcfg;

int main() {
    spdlog::set_level(spdlog::level::debug);
    SSMap properties{
            {"protocol", "consul"},
    };
    ConfigServicePtr cs = RTCFG::GetConfigService(properties);
    String key = "foo";
    spdlog::info("key: {}, value: {}", key, cs->Get(key));
    spdlog::info("key: {}, value: {}", key, cs->Cache(key));
    return 0;
}