#pragma once

#include "../ecs/Component.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace rl {
    class Camera : public Component<Camera> {
    public:

        float fov = 90;
        float nearPlane = 0.01f;
        float farPlane = 1000;

        static Camera* GetMain();
        static void SetMain(Camera* cam);
        void SetMain();

        inline glm::mat4 GetViewMatrix(float screenWidth, float screenHeight) const noexcept
        {
            return glm::perspectiveLH(glm::radians(fov), screenWidth / screenHeight, nearPlane, farPlane);
        }
    };
}
