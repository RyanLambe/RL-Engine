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
        static void Start(std::shared_ptr<Window> window);
		static void Render();

        static void Resize(int width, int height);

		static GraphicsAPI GetAPI();

	private:
        static int width;
        static int height;

		static std::shared_ptr<Context> context;
		static std::shared_ptr<RenderTarget> target;

        static std::shared_ptr<UniformBuffer> ObjectUniformBuffer;
        static std::shared_ptr<UniformBuffer> SceneUniformBuffer;
	};
}