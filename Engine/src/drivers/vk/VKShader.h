#pragma once

#include "../../graphics/Shader.h"
#include "VKContext.h"

namespace rl
{
    class VKShader : public Shader
    {
    public:
        VKShader(const std::string& vertexShaderPath, const std::string& pixelShaderPath,
                 const std::weak_ptr<VKContext>& contextPtr);

        void Enable() override;

    private:
    };
}
