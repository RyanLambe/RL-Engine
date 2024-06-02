cmake_minimum_required(VERSION 3.15)

project(RLEngine)

set(CMAKE_CXX_STANDARD 20)

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
add_subdirectory(Editor)
#add_subdirectory(Sandbox)
