#pragma once

#include <queue>
#include <optional>
#include <filesystem>

#include "EntityData.h"
#include "../components/Camera.h"
#include "ComponentCollection.h"
#include "SystemManager.h"

namespace rl
{
    class Scene
    {
    public:
        SystemManager systemManager;
        ComponentCollection components;
        Camera* mainCamera = nullptr;

        Scene();

        static Scene& GetScene();
        void Reset()
        {
            systemManager = SystemManager();
            components = ComponentCollection();
        }

        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        inline Entity GetParent(Entity entity)
        {
            const auto data = GetEntityData(entity);
            if (!data)
                return NullEntity;
            return data->parent;
        }
        void SetParent(Entity parent, Entity child);

        inline u32 GetChildCount(Entity entity)
        {
            const auto data = GetEntityData(entity);
            if (!data)
                return 0;
            return data->children.size();
        }

        inline std::vector<Entity> GetChildren(Entity entity)
        {
            auto data = GetEntityData(entity);
            if (!data)
                return {};
            return data->children;
        }

        [[nodiscard]] inline std::vector<Entity> GetRootEntities()
        {
            auto data = GetEntityData(NullEntity);
            if (!data)
                return {};
            return data->children;
        }

        EntityData* GetEntityData(Entity entity)
        {
            if (!entities.contains(entity))
                return nullptr;
            return &entities[entity];
        }

        static void SaveToFile(Scene& scene, const std::filesystem::path& filePath);
        static void LoadFromFile(Scene* scene, const std::filesystem::path& filePath);

    private:
        void RemoveEntityFromParentsChildList(Entity entity);

        std::unordered_map<Entity, EntityData> entities = {};
        std::deque<Entity> deletedEntities = std::deque<Entity>();
        Entity nextEntity = Entity(1);
    };
}
