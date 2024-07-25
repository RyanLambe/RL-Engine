#pragma once

#include "../types/Types.h"
#include "../ecs/Component.h"
#include "../graphics/RenderTarget.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace rl
{
    class Camera : public rl::Component<Camera>
    {
    public:
        f32 fov = 90.0f;
        f32 nearPlane = 0.01f;
        f32 farPlane = 1000.0f;

        static Camera* GetMain();
        static void SetMain(Camera* cam);
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

        [[nodiscard]] void* GetTexture() const
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

        [[nodiscard]] inline glm::mat4 GetViewMatrix(float screenWidth, float screenHeight) const noexcept
        {
            return glm::perspectiveLH(glm::radians(fov), screenWidth / screenHeight, nearPlane, farPlane);
        }

    private:
        std::shared_ptr<RenderTarget> renderTarget = nullptr;

        u32 width = 0;
        u32 height = 0;
    };
}
