cmake_minimum_required(VERSION 3.25)

project(ImGui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

include_directories(imgui)
add_library(ImGui STATIC

        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp

        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_dx11.cpp
        imgui/backends/imgui_impl_win32.cpp

        imgui/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(ImGui PUBLIC ../External/glfw/include)
target_link_libraries(ImGui glfw)
set(LIBS d3d11 D3DCompiler user32.lib Dwmapi.lib)
target_link_libraries(ImGui ${LIBS})

# glfw
set(GLFW_LIBRARY_TYPE "STATIC")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})
add_subdirectory(glfw)

