#pragma once

#include <memory>

namespace rl {
    class Shader {
    public:

        static std::shared_ptr<Shader> Create(const std::string& vertexShaderPath, const std::string& pixelShaderPath);

        virtual void Enable() = 0;

    };
}
