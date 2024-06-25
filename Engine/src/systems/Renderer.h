#pragma once

#include "../ecs/SystemManager.h"

#include "../graphics/GraphicsContext.h"
#include "../graphics/RenderTarget.h"
#include "../graphics/UniformBuffer.h"

namespace rl {
    class Renderer : public System {
    public:
        void Start() override;
        void Update() override;

    private:
        int width = 0;
        int height = 0;

        std::shared_ptr<UniformBuffer> ObjectUniformBuffer;
        std::shared_ptr<UniformBuffer> SceneUniformBuffer;
    };
}
