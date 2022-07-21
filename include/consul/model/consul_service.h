#ifndef RTCFG_SERVICE_INSTANCE_H
#define RTCFG_SERVICE_INSTANCE_H

#include "defines.h"
#include "nlohmann/json.hpp"

namespace rtcfg::consul {
    struct Address {
        String address;
        int port;

        explicit Address(const nlohmann::json &j) :
                address(j["address"].get<String>()),
                port(j["port"].get<int>()) {}
    };

    struct TaggedAddresses {
        Address lan;
        Address wan;

        explicit TaggedAddresses(const nlohmann::json &j) :
                lan(j["lan"].get<nlohmann::json>()),
                wan(j["wan"].get<nlohmann::json>()) {}
    };

    struct Meta {
        SSMap data;

        explicit Meta(const nlohmann::json &j) {
            for (auto &[k, v]: j.items()) {
                data[k] = v;
            }
        }
    };

    struct Node {
        String id;
        String node;
        String address;
        String data_center;
        TaggedAddresses tagged_addresses;
        Meta meta;
        int64_t create_index;
        int64_t modify_index;

        explicit Node(const nlohmann::json &j) :
                id(j["id"].get<String>()),
                node(j["node"].get<String>()),
                address(j["address"].get<String>()),
                data_center(j["data_center"].get<String>()),
                tagged_addresses(j["tagged_addresses"].get<nlohmann::json>()),
                meta(j["meta"].get<nlohmann::json>()),
                create_index(j["create_index"].get<int64_t>()),
                modify_index(j["modify_index"].get<int64_t>()) {}
    };

    struct ServiceWeights {
        int passing;
        int warning;

        explicit ServiceWeights(const nlohmann::json &j) :
                passing(j["passing"].get<int>()),
                warning(j["warning"].get<int>()) {}
    };

    struct Service {
        String id;
        String service;
        Vector<String> tags;
        String address;
        Meta meta;
        int port;
        bool enable_tag_override;
        TaggedAddresses tagged_addresses;
        int64_t create_index;
        int64_t modify_index;
        String name_space;

        explicit Service(const nlohmann::json &j) :
                id(j["id"].get<String>()),
                service(j["service"].get<String>()),
                address(j["address"].get<String>()),
                meta(j["meta"].get<nlohmann::json>()),
                port(j["port"].get<int>()),
                enable_tag_override(j["enable_tag_override"].get<bool>()),
                tagged_addresses(j["tagged_addresses"].get<nlohmann::json>()),
                create_index(j["create_index"].get<int64_t>()),
                modify_index(j["modify_index"].get<int64_t>()),
                name_space(j["name_space"].get<String>()) {
            auto &tgs = j["tags"];
            tags.resize(tgs.size());
            for (auto &v : tgs) {
                tags.emplace_back(v);
            }
        }
    };

    struct Check {
        String node;
        String check_id;
        String name;
        String status;
        String notes;
        String output;
        String service_id;
        String service_name;
        Vector<String> service_tags;
        String name_space;
    };

    struct PassingServices {
        Node node;
        Service service;
        Vector<Check> checks;

        explicit PassingServices(const nlohmann::json &j) :
                node(j["nod"].get<nlohmann::json>()),
                service(j["service"].get<nlohmann::json>()) {
        }
    };

    typedef std::shared_ptr<PassingServices> PassingServicesPtr;
}

#endif //RTCFG_SERVICE_INSTANCE_H
