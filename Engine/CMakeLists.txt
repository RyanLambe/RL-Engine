cmake_minimum_required(VERSION 3.25)

# create Engine lib
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

add_library(Engine STATIC
        # dx11 implementation
        src/drivers/dx11/dx11Context.cpp
        src/drivers/dx11/dx11Context.h
        src/drivers/dx11/dx11IndexBuffer.cpp
        src/drivers/dx11/dx11IndexBuffer.h
        src/drivers/dx11/dx11RenderTarget.cpp
        src/drivers/dx11/dx11RenderTarget.h
        src/drivers/dx11/dx11VertexBuffer.cpp
        src/drivers/dx11/dx11VertexBuffer.h

        # graphics
        src/graphics/Context.cpp
        src/graphics/Context.h
        src/graphics/IndexBuffer.cpp
        src/graphics/IndexBuffer.h
        src/graphics/Renderer.cpp
        src/graphics/Renderer.h
        src/graphics/RenderTarget.cpp
        src/graphics/RenderTarget.h
        src/graphics/VertexBuffer.cpp
        src/graphics/VertexBuffer.h

        # objects
        src/objects/Camera.cpp
        src/objects/Camera.h
        src/objects/DirectionalLight.cpp
        src/objects/DirectionalLight.h
        src/objects/Entity.cpp
        src/objects/Entity.h
        src/objects/MeshRenderer.cpp
        src/objects/MeshRenderer.h
        src/objects/PointLight.cpp
        src/objects/PointLight.h

        # types
        src/types/Material.cpp
        src/types/Material.h
        src/types/Mesh.cpp
        src/types/Mesh.h
        src/types/Texture.cpp
        src/types/Texture.h
        src/types/Transform.cpp
        src/types/Transform.h
        src/types/Vec2.cpp
        src/types/Vec2.h
        src/types/Vec3.cpp
        src/types/Vec3.h
        src/types/Vertex.h

        # general
        src/SceneManager.cpp
        src/SceneManager.h
        src/core/Timer.h
        src/ecs/SceneManager.cpp
        src/ecs/SceneManager.h
        src/ecs/ComponentList.h
        src/ecs/Transform.cpp
        src/ecs/Transform.h
        src/core/RLResult.h
        src/core/Logger.h
        src/drivers/dx11/dx11.h
        src/drivers/dx11/dx11.cpp
        src/core/Window.cpp
        src/core/Window.h
        src/drivers/glfw/glfwWindow.cpp
        src/drivers/glfw/glfwWindow.h
        src/core/Application.cpp
        src/core/Application.h
        src/core/Clock.cpp
        src/core/Clock.h
        src/graphics/UniformBuffer.cpp
        src/graphics/UniformBuffer.h
        src/drivers/dx11/dx11UniformBuffer.cpp
        src/drivers/dx11/dx11UniformBuffer.h
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/drivers/dx11/dx11Shader.cpp
        src/drivers/dx11/dx11Shader.h
        src/core/Input.h
        src/drivers/glfw/glfwInput.cpp
        src/core/Key.h
)

# include GLM
target_include_directories(Engine PUBLIC ../External/glm)

# include GLFW
target_compile_definitions(Engine PUBLIC GLFW_EXPOSE_NATIVE_WIN32) # should be defined if using GLFW + DirectX

target_include_directories(Engine PUBLIC ../External/glfw/include)
target_link_libraries(Engine glfw)

# include DirectX 11
set(LIBS d3d11 D3DCompiler user32.lib)
target_link_libraries(Engine ${LIBS})