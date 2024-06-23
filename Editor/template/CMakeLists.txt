cmake_minimum_required(VERSION 3.5)
project(Game)

message("EDITOR_PATH: ${EDITOR_PATH}")
message("RL_BUILD_FLAGS: ${RL_BUILD_FLAGS}")
message("RL_BUILD_CONFIG_FLAGS: ${RL_BUILD_CONFIG_FLAGS}")
message("RL_DEBUG_LEVEL: ${RL_DEBUG_LEVEL}")

set(CMAKE_CXX_FLAGS_RELEASE ${RL_BUILD_CONFIG_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${RL_BUILD_CONFIG_FLAGS})
set(CMAKE_CXX_FLAGS ${RL_BUILD_FLAGS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/ProjectData/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/ProjectData/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/ProjectData/out)

find_library(GLFW NAMES glfw3 PATHS ${EDITOR_PATH})
find_library(ENGINE NAMES Engine PATHS ${EDITOR_PATH})

add_library(Game SHARED ProjectData/Setup.cpp ProjectData/Setup.h
        # .cpp files within project
        Assets/Example.cpp

        # .h files within project
        Assets/Example.h
)

target_include_directories(Game PUBLIC ${EDITOR_PATH}/include)
target_include_directories(Game PUBLIC ${EDITOR_PATH}/ThirdParty/glm)
target_include_directories(Game PUBLIC ${EDITOR_PATH}/ThirdParty/glfw)
target_link_libraries(Game PRIVATE ${GLFW})
target_link_libraries(Game PRIVATE ${ENGINE})

target_compile_definitions(Game PUBLIC _ITERATOR_DEBUG_LEVEL=${RL_DEBUG_LEVEL})
