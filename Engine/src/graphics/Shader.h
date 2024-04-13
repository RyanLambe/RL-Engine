#pragma once

#include <memory>
#include <string>
#include "Context.h"

namespace rl {
    class Shader {
    public:

        static std::shared_ptr<Shader> Create(const std::string& vertexShaderPath, const std::string& pixelShaderPath, const std::weak_ptr<Context>& context);

        virtual void Enable() = 0;
    };
}
