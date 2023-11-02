#include "constants/constants.h"

namespace rtcfg {
    String const KEY_PROTOCOL = "protocol";
    String const KEY_HOST = "host";
    String const KEY_CONSUL = "consul";
    String const KEY_CONSUL_INDEX = "X-Consul-Index";

    String const CONSUL_DEFAULT_URL = "http://127.0.0.1:8500";
    String const CONSUL_KV_PREFIX = "/v1/kv/";
    String const CONSUL_HEALTH_SERVICE = "/v1/health/service/";

    SSMap const EMPTY_SS_MAP{};
    SSMap const CONSUL_KV_KEYS{{"keys", ""}};
    SSMap const CONSUL_KV_RECURSE{{"recurse", ""}};
}