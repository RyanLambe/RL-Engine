cmake_minimum_required(VERSION 3.25)
project(RLEngine)

set(CMAKE_CXX_STANDARD 20)

# settings
set(RL_USE_GLFW 1)
#set(RL_USE_WIN32 1)

set(RL_USE_DX11 1)
#set(RL_USE_VULKAN 1)

# include dependencies
add_subdirectory(External)

# get build flags
set(RL_BUILD_FLAGS ${CMAKE_CXX_FLAGS})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(RL_BUILD_CONFIG_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(RL_BUILD_CONFIG_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
else()
    message(FATAL_ERROR "CMake Build Type Not Supported.")
endif()

# include project
add_subdirectory(Engine)
#add_subdirectory(Editor)
add_subdirectory(Sandbox)
