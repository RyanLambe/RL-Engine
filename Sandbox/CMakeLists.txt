cmake_minimum_required(VERSION 3.5)

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Sandbox src/main.cpp)

# build shaders
add_custom_target(shaders)
set(HLSL_SHADER_FILES shaders/VertexShader.hlsl shaders/PixelShader.hlsl)

set_source_files_properties(shaders/VertexShader.hlsl PROPERTIES ShaderType "vs_5_0")
set_source_files_properties(shaders/PixelShader.hlsl PROPERTIES ShaderType "ps_5_0")

foreach(FILE ${HLSL_SHADER_FILES})
    get_filename_component(FILE_WE ${FILE} NAME_WE)
    get_source_file_property(shadertype ${FILE} ShaderType)

    add_custom_command(
            TARGET shaders
            COMMAND fxc.exe /nologo /Emain /T${shadertype} $<IF:$<CONFIG:DEBUG>,/Od,/O1> /Zi /Fo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${FILE_WE}.cso /Fd ${CMAKE_BINARY_DIR}/${FILE_WE}.pdb ${FILE}
            MAIN_DEPENDENCY ${FILE}
            COMMENT "HLSL ${FILE}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
    )
endforeach(FILE)

add_dependencies(Sandbox shaders)

# add Engine
include_directories(Sandbox ../Engine/src)
target_link_libraries(Sandbox Engine)