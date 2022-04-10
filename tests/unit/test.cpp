#include "rtcfg.h"
#include "spdlog/spdlog.h"

using namespace rtcfg;

int main() {
    SSMap properties{
            {"protocol", "consul"},
    };
    String key = "foo";
    ConfigServicePtr cs = RTCFG::GetConfigService(properties);
    auto value = cs->Get(key);
    spdlog::info("key: {}, value: {}", key, value);
    return 0;
}