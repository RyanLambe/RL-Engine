#pragma once

#include <memory>
#include <utility>

#include "Context.h"
#include "RenderTarget.h"

#include "UniformBuffer.h"
#include "Shader.h"


namespace rl {
	class Renderer
	{
	public:

        Renderer() = delete;
        explicit Renderer(const std::shared_ptr<Window>& window);

        void Render();
        void RenderToWindow();
        void Present();

        void ResizeTarget(int width, int height);
        void EnableTarget();

        std::weak_ptr<Context> GetContext();
        void* GetRenderTexture();

        void* GetDXDevice();
        void* GetDXContext();

        static GraphicsAPI GetAPI();

	private:
        int width;
        int height;

		std::shared_ptr<Context> context;
		std::shared_ptr<RenderTarget> target;

        std::shared_ptr<UniformBuffer> ObjectUniformBuffer;
        std::shared_ptr<UniformBuffer> SceneUniformBuffer;
	};
}