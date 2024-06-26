#pragma once

#include <memory>
#include <string>
#include "GraphicsContext.h"

namespace rl {
    class Shader {
    public:
        virtual ~Shader() = default;

        static std::shared_ptr<Shader> Create(const std::string& vertexShaderPath, const std::string& pixelShaderPath, const std::weak_ptr<GraphicsContext>& context);

        virtual void Enable() = 0;
    };
}
