#pragma once

#include "../ecs/Component.h"
#include "../graphics/RenderTarget.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace rl
{
    class Camera : public Component<Camera>
    {
    public:
        float fov = 90;
        float nearPlane = 0.01f;
        float farPlane = 1000;

        static Camera *GetMain();
        static void SetMain(Camera *cam);
        void SetMain();
        [[nodiscard]] bool IsMain() const;

        void RenderToWindow();
        void RenderToTarget(uint32_t width, uint32_t height);

        void EnableTarget();
        void ResizeTarget(uint32_t w, uint32_t h);

        [[nodiscard]] inline std::shared_ptr<RenderTarget> GetRenderTarget() const
        {
            return renderTarget;
        }

        [[nodiscard]] void *GetTexture() const
        {
            return renderTarget->GetTexture();
        }

        [[nodiscard]] inline uint32_t GetWidth() const
        {
            return width;
        }

        [[nodiscard]] inline uint32_t GetHeight() const
        {
            return height;
        }

        inline glm::mat4 GetViewMatrix(float screenWidth, float screenHeight) const noexcept
        {
            return glm::perspectiveLH(glm::radians(fov), screenWidth / screenHeight, nearPlane, farPlane);
        }

    private:
        std::shared_ptr<RenderTarget> renderTarget = nullptr;

        uint32_t width = 0;
        uint32_t height = 0;
    };
} // namespace rl
