#pragma once

#include "../types/Types.h"

namespace rl
{
    class EntityData
    {
    public:
        Entity id = NullEntity;
        std::string name = "root";
        bool enabled = true;
        bool collapsed = false;

        Entity parent = NullEntity;
        std::vector<Entity> children = {};

        std::unordered_map<std::string, std::unordered_map<std::string, Variable>> componentData = {};
        std::vector<std::string> componentOrder = {};

        EntityData(Entity id) : id(id)
        {
            name = "Entity " + std::to_string(id);
        }
        EntityData() = default;
    };

    static void from_json(const json& j, EntityData& val)
    {
        val.id = j["id"];
        val.name = j["name"];
        val.enabled = j["enabled"];
        val.collapsed = j["collapsed"];
        val.parent = j["parent"];

        val.children = j["children"].get<std::vector<Entity>>();
        val.componentOrder = j["componentOrder"].get<std::vector<std::string>>();
        val.componentData
            = j["componentData"].get<std::unordered_map<std::string, std::unordered_map<std::string, Variable>>>();
    }

    static void to_json(json& j, const EntityData& val)
    {
        j["id"] = val.id;
        j["name"] = val.name;
        j["enabled"] = val.enabled;
        j["collapsed"] = val.collapsed;
        j["parent"] = val.parent;

        j["children"] = val.children;
        j["componentOrder"] = val.componentOrder;
        j["componentData"] = val.componentData;
    }
}
