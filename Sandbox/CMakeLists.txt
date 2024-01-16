cmake_minimum_required(VERSION 3.5)

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_WIN32_EXECUTABLE 1)

add_executable(Sandbox src/main.cpp)

if (MSVC)
    #set_target_properties(Sandbox PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
else()

endif()

include_directories(Sandbox ../Engine/src)
target_link_libraries(Sandbox Engine)