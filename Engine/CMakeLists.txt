cmake_minimum_required(VERSION 3.25)

# *********************
# *** Project Setup ***
# *********************
project(Engine)

# cmake settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

# *********************
# *** Drivers Setup ***
# *********************
set(RL_DRIVERS)

# add system drivers
set(RL_USING_SYSTEM_DRIVER 0)
if (DEFINED RL_USE_WINDOWS)
    set(RL_DRIVERS ${RL_DRIVERS}
            src/drivers/windows/WINDynamicLibrary.cpp
            src/drivers/windows/WINDynamicLibrary.h
    )
    add_compile_definitions(RL_USE_WINDOWS)
    set(RL_USING_WINDOW_DRIVER 1)
endif()

if (DEFINED RL_USE_LINUX)
    message(FATAL_ERROR "Linux is not currently supported.")
endif()

if (RL_USING_WINDOW_DRIVER EQUAL 0)
    message(FATAL_ERROR "No System Driver has been specified.")
endif()

# add window driver
set(RL_USING_WINDOW_DRIVER 0)
if (DEFINED RL_USE_GLFW)
    set(RL_DRIVERS ${RL_DRIVERS}
            src/drivers/glfw/glfwInput.cpp
            src/drivers/glfw/glfwInput.h
            src/drivers/glfw/glfwWindow.cpp
            src/drivers/glfw/glfwWindow.h
    )
    add_compile_definitions(RL_USE_GLFW)
    set(RL_USING_WINDOW_DRIVER 1)
endif()

if (DEFINED RL_USE_WIN32)
    message(FATAL_ERROR "Win32 is not currently supported.")
endif()

if (RL_USING_WINDOW_DRIVER EQUAL 0)
    message(FATAL_ERROR "No Window Driver has been specified.")
endif()

# add graphics driver
set(RL_USING_GRAPHICS_DRIVER 0)
if (DEFINED RL_USE_DX11)
    set(RL_DRIVERS ${RL_DRIVERS}
            src/drivers/dx11/DX11.cpp
            src/drivers/dx11/DX11.h
            src/drivers/dx11/DX11Context.cpp
            src/drivers/dx11/DX11Context.h
            src/drivers/dx11/DX11IndexBuffer.cpp
            src/drivers/dx11/DX11IndexBuffer.h
            src/drivers/dx11/DX11RenderTarget.cpp
            src/drivers/dx11/DX11RenderTarget.h
            src/drivers/dx11/DX11Shader.cpp
            src/drivers/dx11/DX11Shader.h
            src/drivers/dx11/DX11UniformBuffer.cpp
            src/drivers/dx11/DX11UniformBuffer.h
            src/drivers/dx11/DX11VertexBuffer.cpp
            src/drivers/dx11/DX11VertexBuffer.h
    )
    add_compile_definitions(RL_USE_DX11)
    set(RL_USING_GRAPHICS_DRIVER 1)
endif()

if (DEFINED RL_USE_VULKAN)
    set(RL_DRIVERS ${RL_DRIVERS}
            src/drivers/vk/VKContext.cpp
            src/drivers/vk/VKContext.h
            src/drivers/vk/VKIndexBuffer.cpp
            src/drivers/vk/VKIndexBuffer.h
            src/drivers/vk/VKRenderTarget.cpp
            src/drivers/vk/VKRenderTarget.h
            src/drivers/vk/VKShader.cpp
            src/drivers/vk/VKShader.h
            src/drivers/vk/VKUniformBuffer.cpp
            src/drivers/vk/VKUniformBuffer.h
            src/drivers/vk/VKVertexBuffer.cpp
            src/drivers/vk/VKVertexBuffer.h
    )
    add_compile_definitions(RL_USE_VULKAN)
    set(RL_USING_GRAPHICS_DRIVER 1)
endif()

if (RL_USING_GRAPHICS_DRIVER EQUAL 0)
    message(FATAL_ERROR "No Graphics Driver has been specified.")
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
        src/core/Axis.h
        src/core/Clock.cpp
        src/core/Clock.h
        src/core/DynamicLibrary.cpp
        src/core/DynamicLibrary.h
        src/core/GameContext.cpp
        src/core/GameContext.h
        src/core/Input.cpp
        src/core/Input.h
        src/core/Key.h
        src/core/Logger.cpp
        src/core/Logger.h
        src/core/RLResult.h
        src/core/Timer.h
        src/core/Window.cpp
        src/core/Window.h

        # graphics
        src/graphics/GraphicsContext.cpp
        src/graphics/GraphicsContext.h
        src/graphics/IndexBuffer.cpp
        src/graphics/IndexBuffer.h
        src/graphics/RenderTarget.cpp
        src/graphics/RenderTarget.h
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/graphics/UniformBuffer.cpp
        src/graphics/UniformBuffer.h
        src/graphics/VertexBuffer.cpp
        src/graphics/VertexBuffer.h

        # ecs
        src/ecs/Component.cpp
        src/ecs/Component.h
        src/ecs/ComponentCollection.h
        src/ecs/ComponentType.h
        src/ecs/Scene.cpp
        src/ecs/Scene.h
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

        # systems
        src/systems/Renderer.cpp
        src/systems/Renderer.h

        # assets
        src/assets/Asset.cpp
        src/assets/Asset.h
        src/assets/Mesh.cpp
        src/assets/Mesh.h

        # types
        src/types/Vertex.h
        src/types/Types.h
        src/types/OptionalVector.h

        # files
        src/files/FileParser.h
)

# *************************
# *** Include Libraries ***
# *************************

# include common libraries
target_include_directories(Engine PUBLIC ../External/glm)
target_include_directories(Engine PUBLIC ../External/json/include)

# include window driver
if(DEFINED RL_USE_GLFW)
    target_include_directories(Engine PRIVATE ../External/glfw/include)
    target_link_libraries(Engine PRIVATE glfw)
endif()

# include graphics driver
if(DEFINED RL_USE_DX11)
    target_compile_definitions(Engine PRIVATE GLFW_EXPOSE_NATIVE_WIN32)
    set(LIBS d3d11 D3DCompiler user32.lib)
    target_link_libraries(Engine PRIVATE ${LIBS})
endif()

if(DEFINED RL_USE_VULKAN)
    target_include_directories(Engine PUBLIC ../External/vulkan/include)
    target_link_libraries(Engine PRIVATE vulkan)
endif ()


# *****************************
# *** Create Include Folder ***
# *****************************
set(ENGINE_HEADER_DIRS
        /assets
        /components
        /core
        /drivers/glfw
        /drivers/dx11
        /drivers/vk
        /ecs
        /files
        /graphics
        /systems
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

# include json in output
file(COPY ${CMAKE_SOURCE_DIR}/External/json/include DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/ThirdParty/json)
