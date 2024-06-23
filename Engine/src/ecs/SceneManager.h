#pragma once

#include "ComponentCollection.h"

namespace rl {

    class Scene {
    public:
        // systems
        ComponentCollection components;

        static Scene& MainScene();
    };

    class SceneManager {

    };
}
