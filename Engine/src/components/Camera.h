#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../ecs/Component.h"
#include "../graphics/RenderTarget.h"

namespace rl {
    class Camera : public Component<Camera> {
    public:
        float fov = 90;
        float nearPlane = 0.01f;
        float farPlane = 1000;

        static Camera* GetMain();
        static void SetMain(Camera* cam);
        void SetMain();
        bool IsMain() const;

        inline glm::mat4 GetViewMatrix(float screenWidth, float screenHeight) const noexcept
        {
            return glm::perspectiveLH(glm::radians(fov), screenWidth / screenHeight, nearPlane, farPlane);
        }

        void RenderToWindow();

        void RenderToTarget(uint32_t width, uint32_t height);

        [[nodiscard]] inline std::shared_ptr<RenderTarget> GetRenderTarget() const
        {
            return renderTarget;
        }

        void ResizeTarget(uint32_t w, uint32_t h);
        [[nodiscard]] uint32_t GetWidth() const;
        [[nodiscard]] uint32_t GetHeight() const;

        void EnableTarget();
        [[nodiscard]] void* GetTexture() const;

    private:
        std::shared_ptr<RenderTarget> renderTarget = nullptr;

        uint32_t width = 0;
        uint32_t height = 0;
    };
}
