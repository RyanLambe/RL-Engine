#pragma once

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

        static Scene& MainScene();
        void Reset()
        {
            systemManager = SystemManager();
            components = ComponentCollection();
        }
    };

    class SceneManager
    {};
} // namespace rl
