cmake_minimum_required(VERSION 3.25)

# create Engine lib
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

add_library(Engine STATIC
        # dx11 implementation
        src/drivers/dx11/dx11-Context.cpp
        src/drivers/dx11/dx11-Context.h
        src/drivers/dx11/dx11-IndexBuffer.cpp
        src/drivers/dx11/dx11-IndexBuffer.h
        src/drivers/dx11/dx11-RenderTarget.cpp
        src/drivers/dx11/dx11-RenderTarget.h
        src/drivers/dx11/dx11-VertexBuffer.cpp
        src/drivers/dx11/dx11-VertexBuffer.h

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
        src/types/Shader.cpp
        src/types/Shader.h
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
        src/Debug.cpp
        src/Debug.h
        src/Input.cpp
        src/Input.h
        src/SceneManager.cpp
        src/SceneManager.h
        src/Clock.cpp
        src/Clock.h
        src/Window.cpp
        src/Window.h
        )

# include GLM
target_include_directories(Engine PUBLIC ../External/glm)

# include DirectX 11
set(LIBS d3d11 D3DCompiler user32.lib)
target_link_libraries(Engine ${LIBS})