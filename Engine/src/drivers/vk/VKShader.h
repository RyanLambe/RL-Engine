#pragma once

#include "VKContext.h"

#include "../../graphics/Shader.h"

namespace rl {
    class VKShader : public Shader {
    public:
        VKShader(const std::string& vertexShaderPath, const std::string& pixelShaderPath, const std::weak_ptr<VKContext>& contextPtr);

        void Enable() override;

    private:

    };
}
