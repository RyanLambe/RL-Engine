#include "CodeManager.h"

#include <fstream>

#include "FileParser.h"
#include "core/Logger.h"

namespace rl::ed
{
    std::vector<std::string> CodeManager::systems = {};
    std::vector<std::string> CodeManager::components = {};

    std::unordered_map<std::string, std::string> CodeManager::cppFiles = {};
    std::unordered_map<std::string, std::string> CodeManager::headerFiles = {};
    std::unordered_map<std::string, std::string> CodeManager::builtInFiles = {};

    std::unordered_map<std::string, std::vector<std::pair<VariableType, std::string>>> CodeManager::componentVariables
        = {};

    void CodeManager::AddSystem(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile)
    {
        if (cppFile.stem() != headerFile.stem())
        {
            RL_LOG_ERROR("Cpp files and Header files must have the same name.");
            return;
        }

        if (builtInFiles.contains(headerFile.stem().string()) || cppFiles.contains(cppFile.stem().string())
            || headerFiles.contains(headerFile.stem().string()))
        {
            RL_LOG_ERROR("The file: ", cppFile.stem().string(), " already exists.");
            return;
        }

        systems.push_back(cppFile.stem().string());
        cppFiles[cppFile.stem().string()] = cppFile.string();
        headerFiles[headerFile.stem().string()] = headerFile.string();
    }

    void CodeManager::AddComponent(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile)
    {
        if (cppFile.stem() != headerFile.stem())
        {
            RL_LOG_ERROR("Cpp files and Header files must have the same name.");
            return;
        }

        if (builtInFiles.contains(headerFile.stem().string()) || cppFiles.contains(cppFile.stem().string())
            || headerFiles.contains(headerFile.stem().string()))
        {
            RL_LOG_ERROR("The file: ", cppFile.stem().string(), " already exists.");
            return;
        }

        components.push_back(cppFile.stem().string());
        cppFiles[cppFile.stem().string()] = cppFile.string();
        headerFiles[headerFile.stem().string()] = headerFile.string();
    }

    void CodeManager::AddBuiltInSystem(const std::filesystem::path& headerFile)
    {
        if (builtInFiles.contains(headerFile.stem().string()) || headerFiles.contains(headerFile.stem().string()))
        {
            RL_LOG_ERROR("The file: ", headerFile.stem().string(), " already exists.");
            return;
        }

        systems.push_back(headerFile.stem().string());
        builtInFiles[headerFile.stem().string()] = headerFile.string();
    }

    void CodeManager::AddBuiltInComponent(const std::filesystem::path& headerFile)
    {
        if (builtInFiles.contains(headerFile.stem().string()) || headerFiles.contains(headerFile.stem().string()))
        {
            RL_LOG_ERROR("The file: ", headerFile.stem().string(), " already exists.");
            return;
        }

        components.push_back(headerFile.stem().string());
        builtInFiles[headerFile.stem().string()] = headerFile.string();
    }

    const std::vector<std::string>& CodeManager::GetSystems()
    {
        return systems;
    }

    const std::vector<std::string>& CodeManager::GetComponents()
    {
        return components;
    }

    void CodeManager::AddSystem(const std::string& system)
    {
        ProjectManager::RunFunction<void>("AddSystem", system);
    }

    const std::vector<std::pair<VariableType, std::string>>& CodeManager::GetProperties(const std::string& component)
    {
        return componentVariables[component];
    }

    void CodeManager::AddComponent(const std::string& component, rl::Entity entity)
    {
        ProjectManager::RunFunction<void>("AddComponent", component, entity);
    }

    void CodeManager::RemoveComponent(const std::string& component, rl::Entity entity)
    {
        ProjectManager::RunFunction<void>("RemoveComponent", component, entity);
    }

    void* CodeManager::GetComponent(const std::string& component, rl::Entity entity)
    {
        return ProjectManager::RunFunction<void*>("GetComponent", component, entity);
    }

    void CodeManager::GetComponentValue(const VariableType& valType, const std::string& componentType,
                                        const std::string& varName, const Entity& entity, void* outBuf)
    {
        void* temp
            = ProjectManager::RunFunction<void*>("GetValue" + ToStringUpper(valType), componentType, varName, entity);
        if (temp == nullptr)
            return;
        switch (valType)
        {
            case VariableType::Unknown:
                break;
            case VariableType::I8:
                *(i8*)outBuf = *std::bit_cast<i8*>(temp);
                break;
            case VariableType::I16:
                *(i16*)outBuf = *std::bit_cast<i16*>(temp);
                break;
            case VariableType::I32:
                *(i32*)outBuf = *std::bit_cast<i32*>(temp);
                break;
            case VariableType::I64:
                *(i64*)outBuf = *std::bit_cast<i64*>(temp);
                break;
            case VariableType::U8:
                *(u8*)outBuf = *(u8*)temp;
                break;
            case VariableType::U16:
                *(u16*)outBuf = *(u16*)temp;
                break;
            case VariableType::U32:
                *(u32*)outBuf = *(u32*)temp;
                break;
            case VariableType::U64:
                *(u64*)outBuf = *(u64*)temp;
                break;
            case VariableType::F32:
                *(f32*)outBuf = *(f32*)temp;
                break;
            case VariableType::F64:
                *(f64*)outBuf = *(f64*)temp;
                break;
            case VariableType::VEC2:
                *(Vec2*)outBuf = *(Vec2*)temp;
                break;
            case VariableType::VEC3:
                *(Vec3*)outBuf = *(Vec3*)temp;
                break;
            case VariableType::VEC4:
                *(Vec4*)outBuf = *(Vec4*)temp;
                break;
            case VariableType::QUAT:
                *(Quaternion*)outBuf = *(Quaternion*)temp;
                break;
        }
    }

    void CodeManager::Generate()
    {
        componentVariables = {};
        for (const auto& component : components)
        {
            ParseComponent(component);
        }
        GenerateCmake();
        GenerateSetupCpp();
        GenerateSetupHeader();
    }

    void CodeManager::GenerateCmake()
    {
        std::ofstream file(ProjectManager::GetProjectDirectory() + "/CMakeLists.txt");
        if (!file.is_open())
        {
            RL_LOG_ERROR("Unable to open file at: ", ProjectManager::GetProjectDirectory() + "/CMakeLists.txt", ".");
            return;
        }

        file << "cmake_minimum_required(VERSION 3.5)\n"
             << "project(Game)\n\n"
             << "message(\"EDITOR_PATH: ${EDITOR_PATH}\")\n"
             << "message(\"RL_BUILD_FLAGS: ${RL_BUILD_FLAGS}\")\n"
             << "message(\"RL_BUILD_CONFIG_FLAGS: ${RL_BUILD_CONFIG_FLAGS}\")\n"
             << "message(\"RL_DEBUG_LEVEL: ${RL_DEBUG_LEVEL}\")\n\n"
             << "set(CMAKE_CXX_FLAGS_RELEASE ${RL_BUILD_CONFIG_FLAGS})\n"
             << "set(CMAKE_CXX_FLAGS_DEBUG ${RL_BUILD_CONFIG_FLAGS})\n"
             << "set(CMAKE_CXX_FLAGS ${RL_BUILD_FLAGS})\n\n"
             << "set(CMAKE_CXX_STANDARD 20)\n"
             << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/ProjectData/out)\n"
             << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/ProjectData/out)\n"
             << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/ProjectData/out)\n\n"
             << "find_library(GLFW NAMES glfw3 PATHS ${EDITOR_PATH})\n"
             << "find_library(ENGINE NAMES Engine PATHS ${EDITOR_PATH})\n\n"
             << "add_library(Game SHARED ProjectData/Setup.cpp ProjectData/Setup.h\n"
             << "\t# .cpp files within project\n";

        for (const auto& cppFile : cppFiles)
        {
            file << cppFile.second << "\n";
        }

        file << "\n\t# .h files within project\n";

        for (const auto& hFile : headerFiles)
        {
            file << hFile.second << "\n";
        }

        file << ")\n\n"
             << "target_include_directories(Game PUBLIC ${EDITOR_PATH}/include)\n"
             << "target_include_directories(Game PUBLIC ${EDITOR_PATH}/ThirdParty/glm)\n"
             << "target_include_directories(Game PUBLIC ${EDITOR_PATH}/ThirdParty/glfw)\n"
             << "target_link_libraries(Game PRIVATE ${GLFW})\n"
             << "target_link_libraries(Game PRIVATE ${ENGINE})\n\n"
             << "target_compile_definitions(Game PUBLIC _ITERATOR_DEBUG_LEVEL=${RL_DEBUG_LEVEL})\n";

        file.close();
    }

    void CodeManager::GenerateSetupCpp()
    {
        std::ofstream file(ProjectManager::GetProjectDirectory() + "/ProjectData/Setup.cpp");
        if (!file.is_open())
        {
            RL_LOG_ERROR("Unable to open file at: ", ProjectManager::GetProjectDirectory() + "/ProjectData/Setup.cpp",
                         ".");
            return;
        }

        file << "#include \"Setup.h\"\n"
             << "#include \"Engine.h\"\n\n";

        for (const auto& hFile : headerFiles)
        {
            file << "#include \"../" << hFile.second << "\"\n";
        }

        file << "\nusing namespace rl;\n\n"
             << "extern \"C\" void GameSetup(void* mainApp) {\n"
             << "\tApplication::ConnectToApp((std::shared_ptr<Application>*)mainApp);\n"
             << "}\n";

        WriteAddSystemFunc(file);

        WriteAddOrRemoveComponentFunc(file, true);
        WriteAddOrRemoveComponentFunc(file, false);
        WriteGetComponentFunc(file);

        WriteSetOrGetValueFunc(file, VariableType::I8, true);
        WriteSetOrGetValueFunc(file, VariableType::I8, false);
        WriteSetOrGetValueFunc(file, VariableType::I16, true);
        WriteSetOrGetValueFunc(file, VariableType::I16, false);
        WriteSetOrGetValueFunc(file, VariableType::I32, true);
        WriteSetOrGetValueFunc(file, VariableType::I32, false);
        WriteSetOrGetValueFunc(file, VariableType::I64, true);
        WriteSetOrGetValueFunc(file, VariableType::I64, false);

        WriteSetOrGetValueFunc(file, VariableType::U8, true);
        WriteSetOrGetValueFunc(file, VariableType::U8, false);
        WriteSetOrGetValueFunc(file, VariableType::U16, true);
        WriteSetOrGetValueFunc(file, VariableType::U16, false);
        WriteSetOrGetValueFunc(file, VariableType::U32, true);
        WriteSetOrGetValueFunc(file, VariableType::U32, false);
        WriteSetOrGetValueFunc(file, VariableType::U64, true);
        WriteSetOrGetValueFunc(file, VariableType::U64, false);

        WriteSetOrGetValueFunc(file, VariableType::F32, true);
        WriteSetOrGetValueFunc(file, VariableType::F32, false);
        WriteSetOrGetValueFunc(file, VariableType::F64, true);
        WriteSetOrGetValueFunc(file, VariableType::F64, false);

        WriteSetOrGetValueFunc(file, VariableType::VEC2, true);
        WriteSetOrGetValueFunc(file, VariableType::VEC2, false);
        WriteSetOrGetValueFunc(file, VariableType::VEC3, true);
        WriteSetOrGetValueFunc(file, VariableType::VEC3, false);
        WriteSetOrGetValueFunc(file, VariableType::VEC4, true);
        WriteSetOrGetValueFunc(file, VariableType::VEC4, false);
        WriteSetOrGetValueFunc(file, VariableType::QUAT, true);
        WriteSetOrGetValueFunc(file, VariableType::QUAT, false);

        file.close();
    }

    void CodeManager::GenerateSetupHeader()
    {
        std::ofstream file(ProjectManager::GetProjectDirectory() + "/ProjectData/Setup.h");
        if (!file.is_open())
        {
            RL_LOG_ERROR("Unable to open file at: ", ProjectManager::GetProjectDirectory() + "/ProjectData/Setup.cpp",
                         ".");
            return;
        }

        file
            << "#pragma once\n"
            << "#include \"Engine.h\"\n\n"
            << "extern \"C\"\n{\n"
            << "__declspec(dllexport) void GameSetup(void* mainApp);\n\n"

            << "__declspec(dllexport) void AddSystem(const std::string& system);\n\n"

            << "__declspec(dllexport) void AddComponent(const std::string& componentType, const rl::Entity& entity);\n"
            << "__declspec(dllexport) void RemoveComponent(const std::string& componentType, const rl::Entity& "
               "entity);\n"
            << "__declspec(dllexport) void* GetComponent(const std::string& componentType, const rl::Entity& "
               "entity);\n\n"

            << "__declspec(dllexport) void SetValueI8(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const i8& val);\n"
            << "__declspec(dllexport) void SetValueI16(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const i16& val);\n"
            << "__declspec(dllexport) void SetValueI32(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const i32& val);\n"
            << "__declspec(dllexport) void SetValueI64(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const i64& val);\n\n"

            << "__declspec(dllexport) void* GetValueI8(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueI16(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueI32(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueI64(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n\n"

            << "__declspec(dllexport) void SetValueU8(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const u8& val);\n"
            << "__declspec(dllexport) void SetValueU16(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const u16& val);\n"
            << "__declspec(dllexport) void SetValueU32(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const u32& val);\n"
            << "__declspec(dllexport) void SetValueU64(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const u64& val);\n\n"

            << "__declspec(dllexport) void* GetValueU8(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueU16(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueU32(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueU64(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n\n"

            << "__declspec(dllexport) void SetValueF32(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const f32& val);\n"
            << "__declspec(dllexport) void SetValueF64(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const f64& val);\n\n"

            << "__declspec(dllexport) void* GetValueF32(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueF64(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n\n"

            << "__declspec(dllexport) void SetValueVec2(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const Vec2& val);\n"
            << "__declspec(dllexport) void SetValueVec3(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const Vec3& val);\n"
            << "__declspec(dllexport) void SetValueVec4(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity, const Vec4& val);\n"
            << "__declspec(dllexport) void SetValueQuaternion(const std::string& componentType, const std::string& "
               "varName, "
               "const rl::Entity& entity, const Quaternion& val);\n\n"

            << "__declspec(dllexport) void* GetValueVec2(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueVec3(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueVec4(const std::string& componentType, const std::string& varName, "
               "const rl::Entity& entity);\n"
            << "__declspec(dllexport) void* GetValueQuaternion(const std::string& componentType, const std::string& "
               "varName, "
               "const rl::Entity& entity);\n";

        file << "};\n";

        file.close();
    }

    void CodeManager::ParseComponent(const std::string& component)
    {
        if (!headerFiles.contains(component) && !builtInFiles.contains(component))
        {
            RL_LOG_ERROR("Unable to find component ", component, ". Are you sure it is imported?");
            return;
        }

        std::string path;
        if (headerFiles.contains(component))
        {
            path = ProjectManager::GetProjectDirectory() + headerFiles[component];
        }
        else if (builtInFiles.contains(component))
        {
            path = std::filesystem::current_path().string() + builtInFiles[component];
        }
        else
        {
            RL_LOG_ERROR("Unable to find file for component: ", component, ".");
            return;
        }

        std::ifstream file(path);
        if (!file.is_open())
        {
            RL_LOG_ERROR("Unable to open file at: ", path, ".");
            return;
        }

        std::vector<std::string> words = {};
        FileParser::BreakupFileToWords(words, file);
        file.close();

        bool classDef = false;
        bool publicDef = false;
        int bracketsDeep = 0;
        int goalBracketsDeep = -1;
        for (int i = 0; i < words.size(); i++)
        {
            if (words[i] == "{")
            {
                bracketsDeep++;
                continue;
            }
            if (words[i] == "}")
            {
                if (classDef && bracketsDeep == goalBracketsDeep)
                {
                    classDef = false;
                    break;
                }
                bracketsDeep--;
                continue;
            }

            // Find if in public definitions
            if (classDef && bracketsDeep == goalBracketsDeep && i + 1 < words.size())
            {
                if (words[i] == "public")
                {
                    publicDef = true;
                    continue;
                }
                if (words[i] == "private" || words[i] == "protected")
                {
                    publicDef = false;
                    continue;
                }
            }

            // Find class definition
            if (!classDef && words[i] == "class" && words[i + 1] == component)
            {
                if (words[i + 2] != ":")
                {
                    RL_LOG_ERROR(component, " must inherit from the \"rl::Component\" class.");
                    break;
                }

                i += 3;
                while (i + 6 < words.size() && words[i] != "{")
                {
                    if (words[i] == "public" && words[i + 1] == "rl" && words[i + 2] == "::"
                        && words[i + 3] == "Component" && words[i + 4] == "<" && words[i + 5] == component
                        && words[i + 6] == ">")
                    {
                        classDef = true;
                        publicDef = false;
                        goalBracketsDeep = bracketsDeep + 1;
                        i += 6;
                        break;
                    }
                    i++;
                }
                if (!classDef)
                {
                    RL_LOG_ERROR(component, " must inherit from the \"rl::Component<", component, ">\" class.");
                    break;
                }
                continue;
            }

            // find parameters
            if (classDef && publicDef && bracketsDeep == goalBracketsDeep)
            {
                if (i <= 0 && i + 2 >= words.size())
                    continue;
                if (words[i - 1] == "static" || words[i - 1] == "const") // type preceded by
                    continue;
                if (words[i + 1] == "const" || words[i + 1] == "*") // type followed by
                    continue;
                if (words[i + 2] != ";" && words[i + 2] != "=") // name followed by
                    continue;

                if (!componentVariables.contains(component))
                    componentVariables[component] = {};

                if (words[i] == "f32")
                {
                    componentVariables[component].emplace_back(VariableType::F32, words[i + 1]);
                }
                else if (words[i] == "f64")
                {
                    componentVariables[component].emplace_back(VariableType::F64, words[i + 1]);
                }
                else if (words[i] == "i8")
                {
                    componentVariables[component].emplace_back(VariableType::I8, words[i + 1]);
                }
                else if (words[i] == "i16")
                {
                    componentVariables[component].emplace_back(VariableType::I16, words[i + 1]);
                }
                else if (words[i] == "i32")
                {
                    componentVariables[component].emplace_back(VariableType::I32, words[i + 1]);
                }
                else if (words[i] == "i64")
                {
                    componentVariables[component].emplace_back(VariableType::I64, words[i + 1]);
                }
                else if (words[i] == "u8")
                {
                    componentVariables[component].emplace_back(VariableType::U8, words[i + 1]);
                }
                else if (words[i] == "u16")
                {
                    componentVariables[component].emplace_back(VariableType::U16, words[i + 1]);
                }
                else if (words[i] == "u32")
                {
                    componentVariables[component].emplace_back(VariableType::U32, words[i + 1]);
                }
                else if (words[i] == "u64")
                {
                    componentVariables[component].emplace_back(VariableType::U64, words[i + 1]);
                }
                else if (words[i] == "Vec2")
                {
                    componentVariables[component].emplace_back(VariableType::VEC2, words[i + 1]);
                }
                else if (words[i] == "Vec3")
                {
                    componentVariables[component].emplace_back(VariableType::VEC3, words[i + 1]);
                }
                else if (words[i] == "Vec4")
                {
                    componentVariables[component].emplace_back(VariableType::VEC4, words[i + 1]);
                }
                else if (words[i] == "Quaternion")
                {
                    componentVariables[component].emplace_back(VariableType::QUAT, words[i + 1]);
                }
            }
        }
    }

    void CodeManager::WriteAddSystemFunc(std::ofstream& file)
    {
        file << "\nextern \"C\" void AddSystem(const std::string& system) {\n";

        bool first = true;
        for (const auto& system : systems)
        {
            file << "\t";
            if (!first)
                file << "else ";
            file << "if (system == \"" << system << "\")\n";
            file << "\t\tApplication::GetScene().systemManager.AddSystem<" << system << ">(system);\n";
            first = false;
        }
        file << "}\n";
    }

    void CodeManager::WriteSetOrGetValueFunc(std::ofstream& file, VariableType type, bool writeSetFunc)
    {
        if (writeSetFunc)
        {
            file << "\nextern \"C\" void SetValue" << ToStringUpper(type)
                 << "(const std::string& componentType, const std::string& varName, const Entity& entity, "
                 << "const " << ToString(type) << "& val) {\n";
        }
        else
        {
            file << "\nextern \"C\" void* GetValue" << ToStringUpper(type)
                 << "(const std::string& componentType, const std::string& varName, const Entity& entity) {\n";
        }

        for (const auto& component : components)
        {
            file << "\tif (componentType == \"" << component << "\")\n\t{\n";
            for (const std::pair<VariableType, std::string>& var : componentVariables[component])
            {
                if (var.first != type)
                    continue;
                file << "\t\tif (varName == \"" << var.second << "\")\n\t\t{\n";
                if (writeSetFunc)
                {
                    file << "\t\t\t" << component << "::GetComponent(entity)." << var.second << " = val;\n";
                    file << "\t\t\treturn;\n\t\t}\n";
                }
                else
                {
                    file << "\t\t\treturn &" << component << "::GetComponent(entity)." << var.second << ";\n\t\t}\n";
                }
            }
            if (writeSetFunc)
            {
                file << "\t\treturn;\n\t}\n";
            }
            else
            {
                file << "\t\treturn nullptr;\n\t}\n";
            }
        }
        if (!writeSetFunc)
            file << "\treturn nullptr;\n";
        file << "}\n";
    }

    void CodeManager::WriteAddOrRemoveComponentFunc(std::ofstream& file, bool writeAddFunc)
    {
        file << "\nextern \"C\" void " << (writeAddFunc ? "AddComponent" : "RemoveComponent")
             << "(const std::string& componentType, const Entity& entity) {\n";

        bool first = true;
        for (const auto& component : components)
        {
            file << "\t";
            if (!first)
                file << "else ";
            file << "if (componentType == \"" << component << "\")\n\t{\n";

            if (writeAddFunc)
            {
                file << "\t\tif (!" << component << "::HasComponent(entity))\n";
                file << "\t\t\t" << component << "::Create(entity);\n\t}\n";
            }
            else
            {
                file << "\t\tif (" << component << "::HasComponent(entity))\n";
                file << "\t\t\t" << component << "::Delete(entity);\n\t}\n";
            }

            first = false;
        }

        file << "}\n";
    }

    void CodeManager::WriteGetComponentFunc(std::ofstream& file)
    {
        file << "\nextern \"C\" void* GetComponent(const std::string& componentType, const Entity& entity) {\n";

        for (const auto& component : components)
        {
            file << "\tif (componentType == \"" << component << "\")\n";
            file << "\t\treturn (void*)&" << component << "::GetComponent(entity);\n";
        }
        file << "\treturn nullptr;\n}\n";
    }

    std::string CodeManager::ToString(VariableType type)
    {
        switch (type)
        {
            case VariableType::Unknown:
                return "Unknown";
            case VariableType::I8:
                return "i8";
            case VariableType::I16:
                return "i16";
            case VariableType::I32:
                return "i32";
            case VariableType::I64:
                return "i64";
            case VariableType::U8:
                return "u8";
            case VariableType::U16:
                return "u16";
            case VariableType::U32:
                return "u32";
            case VariableType::U64:
                return "u64";
            case VariableType::F32:
                return "f32";
            case VariableType::F64:
                return "f64";
            case VariableType::VEC2:
                return "Vec2";
            case VariableType::VEC3:
                return "Vec3";
            case VariableType::VEC4:
                return "Vec4";
            case VariableType::QUAT:
                return "Quaternion";
        }
        return "Error";
    }

    std::string CodeManager::ToStringUpper(VariableType type)
    {
        switch (type)
        {
            case VariableType::Unknown:
                return "Unknown";
            case VariableType::I8:
                return "I8";
            case VariableType::I16:
                return "I16";
            case VariableType::I32:
                return "I32";
            case VariableType::I64:
                return "I64";
            case VariableType::U8:
                return "U8";
            case VariableType::U16:
                return "U16";
            case VariableType::U32:
                return "U32";
            case VariableType::U64:
                return "U64";
            case VariableType::F32:
                return "F32";
            case VariableType::F64:
                return "F64";
            case VariableType::VEC2:
                return "Vec2";
            case VariableType::VEC3:
                return "Vec3";
            case VariableType::VEC4:
                return "Vec4";
            case VariableType::QUAT:
                return "Quaternion";
        }
        return "Error";
    }
}