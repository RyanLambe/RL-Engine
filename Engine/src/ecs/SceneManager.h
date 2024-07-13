#pragma once

#include "../components/Camera.h"
#include "ComponentCollection.h"
#include "SystemManager.h"
#include <queue>

namespace rl
{

    class Scene
    {
    public:
        SystemManager systemManager;
        ComponentCollection components;
        Camera* mainCamera = nullptr;

        static Scene& MainScene();
        void Reset()
        {
            systemManager = SystemManager();
            components = ComponentCollection();
        }

        Entity CreateEntity();
        void DestroyEntity(Entity entity);

    private:
        std::vector<Entity> entities = std::vector<Entity>();
        std::queue<Entity> deletedEntities = std::queue<Entity>();
        Entity nextEntity = (Entity)0;
    };

    class SceneManager
    {};
}
