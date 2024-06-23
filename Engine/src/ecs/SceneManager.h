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
    };

    class SceneManager {

    };
}
