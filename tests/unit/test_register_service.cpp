#include "rtcfg.h"
#include "spdlog/spdlog.h"

using namespace rtcfg;

int main() {
    // properties
    spdlog::set_level(spdlog::level::debug);
    SSMap properties{};
    // construct consul
    consul::Consul cs = RTCFG::GetConsul(properties);
    // service cache
    auto &srv = cs.GetNamingService();
    rtcfg::consul::Service service{"echo"};
    srv.Register(service);
    return 0;
}