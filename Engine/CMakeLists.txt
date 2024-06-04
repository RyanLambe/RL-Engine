cmake_minimum_required(VERSION 3.5)

# *********************
# *** Project Setup ***
# *********************
project(Engine)

# cmake settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

# rl engine settings
set(RL_PLATFORM RL_WINDOWS)
set(RL_API RL_DX11)


# *********************
# *** Drivers Setup ***
# *********************
set(RL_DRIVERS)

# platform specific drivers
if(${RL_PLATFORM} STREQUAL RL_WINDOWS)

    set(RL_DRIVERS ${RL_DRIVERS}
            src/drivers/glfw/glfwInput.cpp
            src/drivers/glfw/glfwWindow.cpp
            src/drivers/glfw/glfwWindow.h
    )

elseif (${RL_PLATFORM} STREQUAL RL_LINUX)
    message(FATAL_ERROR "Linux is not currently supported.")
else ()
    message(FATAL_ERROR "No Platform has been specified.")
endif()

# api specific drivers
if(${RL_API} STREQUAL RL_DX11)

    set(RL_DRIVERS ${RL_DRIVERS}
            src/drivers/dx11/dx11.cpp
            src/drivers/dx11/dx11.h
            src/drivers/dx11/dx11Context.cpp
            src/drivers/dx11/dx11Context.h
            src/drivers/dx11/dx11IndexBuffer.cpp
            src/drivers/dx11/dx11IndexBuffer.h
            src/drivers/dx11/dx11RenderTarget.cpp
            src/drivers/dx11/dx11RenderTarget.h
            src/drivers/dx11/dx11Shader.cpp
            src/drivers/dx11/dx11Shader.h
            src/drivers/dx11/dx11UniformBuffer.cpp
            src/drivers/dx11/dx11UniformBuffer.h
            src/drivers/dx11/dx11VertexBuffer.cpp
            src/drivers/dx11/dx11VertexBuffer.h
    )

elseif (${RL_API} STREQUAL RL_OPENGL)
    message(FATAL_ERROR "OpenGL is not currently supported.")
else ()
    message(FATAL_ERROR "No Platform has been specified.")
endif()

# **********************
# *** Create Library ***
# **********************

add_library(Engine STATIC

        ${RL_DRIVERS}
        src/Engine.h

        # core
        src/core/Application.cpp
        src/core/Application.h
        src/core/Clock.cpp
        src/core/Clock.h
        src/core/Input.h
        src/core/Key.h
        src/core/Logger.h
        src/core/RLResult.h
        src/core/Timer.h
        src/core/Window.cpp
        src/core/Window.h

        # graphics
        src/graphics/Context.cpp
        src/graphics/Context.h
        src/graphics/IndexBuffer.cpp
        src/graphics/IndexBuffer.h
        src/graphics/Renderer.cpp
        src/graphics/Renderer.h
        src/graphics/RenderTarget.cpp
        src/graphics/RenderTarget.h
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/graphics/UniformBuffer.cpp
        src/graphics/UniformBuffer.h
        src/graphics/VertexBuffer.cpp
        src/graphics/VertexBuffer.h

        # ecs
        src/ecs/Component.h
        src/ecs/SceneManager.cpp
        src/ecs/SceneManager.h
        src/ecs/SystemManager.cpp
        src/ecs/SystemManager.h

        # components
        src/components/Camera.cpp
        src/components/Camera.h
        src/components/MeshComponent.cpp
        src/components/MeshComponent.h
        src/components/Transform.cpp
        src/components/Transform.h

        # types
        src/types/Vertex.h
        src/types/OptionalVector.h
        src/ecs/ComponentType.h
        src/ecs/ComponentCollection.h

)

# *************************
# *** Include Libraries ***
# *************************

# include GLM
target_include_directories(Engine PUBLIC ../External/glm)

# include Platform
if(RL_PLATFORM STREQUAL RL_WINDOWS)
    target_include_directories(Engine PRIVATE ../External/glfw/include)
    target_link_libraries(Engine PRIVATE glfw)
endif()

# include API
if(RL_API STREQUAL RL_DX11)
    target_compile_definitions(Engine PRIVATE GLFW_EXPOSE_NATIVE_WIN32)
    set(LIBS d3d11 D3DCompiler user32.lib)
    target_link_libraries(Engine PRIVATE ${LIBS})
endif()

# *****************************
# *** Create Include Folder ***
# *****************************
set(ENGINE_HEADER_DIRS
        /components
        /core
        /drivers/glfw
        /drivers/dx11
        /ecs
        /graphics
        /types
        /
)

foreach(DIR ${ENGINE_HEADER_DIRS})
    file(GLOB ENGINE_HEADERS src${DIR}/*.h)
    file(COPY ${ENGINE_HEADERS} DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/include/${DIR})
endforeach(DIR)

# include glm in output
file(COPY ${CMAKE_SOURCE_DIR}/External/glm/glm DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/ThirdParty/glm)
file(COPY ${CMAKE_SOURCE_DIR}/External/glm/copying.txt DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/ThirdParty/glm)


