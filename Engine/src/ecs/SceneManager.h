#pragma once

#include "ComponentCollection.h"
#include "SystemManager.h"
#include "../components/Camera.h"

namespace rl {

    class Scene {
    public:
        SystemManager systemManager;
        ComponentCollection components;
        Camera* mainCamera = nullptr;

        static Scene& MainScene();
        void Reset() {
            systemManager = SystemManager();
            components = ComponentCollection();
        }
    };

    class SceneManager {

    };
}
