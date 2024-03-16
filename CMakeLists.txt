cmake_minimum_required(VERSION 3.5)

project(RL-Engine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(External/glfw)
add_subdirectory(External)

add_subdirectory(Engine)
add_subdirectory(Editor)

# disable sandbox for now
# add_subdirectory(Sandbox)