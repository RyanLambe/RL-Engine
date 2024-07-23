#include "CodeManager.h"

#include "core/Logger.h"
#include "fstream"

namespace rl::ed
{
    std::vector<std::string> CodeManager::systems = {};
    std::vector<std::string> CodeManager::components = {};

    std::unordered_map<std::string, std::string> CodeManager::cppFiles = {};
    std::unordered_map<std::string, std::string> CodeManager::headerFiles = {};

    std::unordered_map<std::string, std::vector<std::pair<VariableType, std::string>>> CodeManager::componentVariables
        = {};

    void CodeManager::AddSystem(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile)
    {
        if (cppFile.stem() != headerFile.stem())
        {
            RL_LOG_ERROR("Cpp files and Header files must have the same name.");
            return;
        }

        if (cppFiles.contains(cppFile.stem().string()) || headerFiles.contains(headerFile.stem().string()))
        {
            RL_LOG_ERROR("The cpp file: ", cppFile.stem(), " already exists.");
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

        if (cppFiles.contains(cppFile.stem().string()) || headerFiles.contains(headerFile.stem().string()))
        {
            RL_LOG_ERROR("The cpp file: ", cppFile.stem(), " already exists.");
            return;
        }

        components.push_back(cppFile.stem().string());
        cppFiles[cppFile.stem().string()] = cppFile.string();
        headerFiles[headerFile.stem().string()] = headerFile.string();
    }

    const std::vector<std::string>& CodeManager::GetSystems()
    {
        return systems;
    }

    const std::vector<std::string>& CodeManager::GetComponents()
    {
        return components;
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

    void CodeManager::GetValue(const VariableType& valType, const std::string& componentType,
                               const std::string& varName, const Entity& entity, void* outBuf)
    {
        switch (valType)
        {
            case VariableType::Unknown:
                return;
            case VariableType::I8:
                *(i8*)outBuf = ProjectManager::RunFunction<i8>("GetValue" + ToStringUpper(valType), componentType,
                                                               varName, entity);
            case VariableType::I16:
                *(i16*)outBuf = ProjectManager::RunFunction<i16>("GetValue" + ToStringUpper(valType), componentType,
                                                                 varName, entity);
            case VariableType::I32:
                *(i32*)outBuf = ProjectManager::RunFunction<i32>("GetValue" + ToStringUpper(valType), componentType,
                                                                 varName, entity);
            case VariableType::I64:
                *(i64*)outBuf = ProjectManager::RunFunction<i64>("GetValue" + ToStringUpper(valType), componentType,
                                                                 varName, entity);
            case VariableType::U8:
                *(u8*)outBuf = ProjectManager::RunFunction<u8>("GetValue" + ToStringUpper(valType), componentType,
                                                               varName, entity);
            case VariableType::U16:
                *(u16*)outBuf = ProjectManager::RunFunction<u16>("GetValue" + ToStringUpper(valType), componentType,
                                                                 varName, entity);
            case VariableType::U32:
                *(u32*)outBuf = ProjectManager::RunFunction<u32>("GetValue" + ToStringUpper(valType), componentType,
                                                                 varName, entity);
            case VariableType::U64:
                *(u64*)outBuf = ProjectManager::RunFunction<u64>("GetValue" + ToStringUpper(valType), componentType,
                                                                 varName, entity);
            case VariableType::F32:
                *(f32*)outBuf = ProjectManager::RunFunction<f32>("GetValue" + ToStringUpper(valType), componentType,
                                                                 varName, entity);
            case VariableType::F64:
                *(f64*)outBuf = ProjectManager::RunFunction<f64>("GetValue" + ToStringUpper(valType), componentType,
                                                                 varName, entity);
            case VariableType::VEC2:
                *(vec2*)outBuf = ProjectManager::RunFunction<vec2>("GetValue" + ToStringUpper(valType), componentType,
                                                                   varName, entity);
            case VariableType::VEC3:
                *(vec3*)outBuf = ProjectManager::RunFunction<vec3>("GetValue" + ToStringUpper(valType), componentType,
                                                                   varName, entity);
            case VariableType::VEC4:
                *(vec4*)outBuf = ProjectManager::RunFunction<vec4>("GetValue" + ToStringUpper(valType), componentType,
                                                                   varName, entity);
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
             << "void GameSetupInternal(void* mainApp);\n\n"
             << "extern \"C\" void GameSetup(void* mainApp) {\n"
             << "\tGameSetupInternal(mainApp);\n"
             << "}\n\n"
             << "void GameSetupInternal(void* mainApp) {\n"
                "\tApplication::ConnectToApp((std::shared_ptr<Application>*)mainApp);\n\n";

        // todo: find better way to add systems that is linked to the scene
        file << "\tApplication::GetScene().systemManager.AddSystem<Renderer>();\n";
        for (const auto& system : systems)
        {
            file << "\tApplication::GetScene().systemManager.AddSystem<" << system << ">();\n";
        }
        file << "}\n";

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

        file << "#pragma once\n"
             << "#include \"Engine.h\"\n\n"
             << "extern \"C\"\n{\n"
             << "__declspec(dllexport) void GameSetup(void* mainApp);\n\n"

             << "__declspec(dllexport) void AddComponent(const std::string& componentType, const rl::Entity& entity);\n"
             << "__declspec(dllexport) void RemoveComponent(const std::string& componentType, const rl::Entity& "
                "entity);\n"
             << "__declspec(dllexport) void* GetComponent(const std::string& componentType, const rl::Entity& "
                "entity);\n\n"

             << "__declspec(dllexport) void SetValueI8(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, i8 val);\n"
             << "__declspec(dllexport) void SetValueI16(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, i16 val);\n"
             << "__declspec(dllexport) void SetValueI32(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, i32 val);\n"
             << "__declspec(dllexport) void SetValueI64(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, i64 val);\n\n"

             << "__declspec(dllexport) i8 GetValueI8(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) i16 GetValueI16(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) i32 GetValueI32(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) i64 GetValueI64(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n\n"

             << "__declspec(dllexport) void SetValueU8(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, u8 val);\n"
             << "__declspec(dllexport) void SetValueU16(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, u16 val);\n"
             << "__declspec(dllexport) void SetValueU32(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, u32 val);\n"
             << "__declspec(dllexport) void SetValueU64(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, u64 val);\n\n"

             << "__declspec(dllexport) u8 GetValueU8(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) u16 GetValueU16(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) u32 GetValueU32(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) u64 GetValueU64(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n\n"

             << "__declspec(dllexport) void SetValueF32(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, f32 val);\n"
             << "__declspec(dllexport) void SetValueF64(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, f64 val);\n\n"

             << "__declspec(dllexport) f32 GetValueF32(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) f64 GetValueF64(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n\n"

             << "__declspec(dllexport) void SetValueVec2(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, vec2 val);\n"
             << "__declspec(dllexport) void SetValueVec3(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, vec3 val);\n"
             << "__declspec(dllexport) void SetValueVec4(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity, vec4 val);\n\n"

             << "__declspec(dllexport) vec2 GetValueVec2(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) vec3 GetValueVec3(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n"
             << "__declspec(dllexport) vec4 GetValueVec4(const std::string& componentType, const std::string& varName, "
                "const rl::Entity& entity);\n";

        file << "};\n";

        file.close();
    }

    void CodeManager::ParseComponent(const std::string& component)
    {
        if (!headerFiles.contains(component))
        {
            RL_LOG_ERROR("Unable to find component ", component, ". Are you sure it is imported?");
            return;
        }
        std::ifstream file(ProjectManager::GetProjectDirectory() + headerFiles[component]);
        if (!file.is_open())
        {
            RL_LOG_ERROR("Unable to open file at: ", ProjectManager::GetProjectDirectory() + headerFiles[component],
                         ".");
            return;
        }

        std::vector<std::string> words = {};
        BreakupHeaderToWords(words, file);
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
                if (words[i] == "public" && words[i + 1] == ":")
                {
                    publicDef = true;
                    i++;
                    continue;
                }
                if ((words[i] == "private" || words[i] == "protected") && words[i + 1] == ":")
                {
                    publicDef = false;
                    i++;
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
                else if (words[i] == "vec2")
                {
                    componentVariables[component].emplace_back(VariableType::VEC2, words[i + 1]);
                }
                else if (words[i] == "vec3")
                {
                    componentVariables[component].emplace_back(VariableType::VEC3, words[i + 1]);
                }
                else if (words[i] == "vec4")
                {
                    componentVariables[component].emplace_back(VariableType::VEC4, words[i + 1]);
                }
            }
        }
    }

    void CodeManager::BreakupHeaderToWords(std::vector<std::string>& words, std::ifstream& file)
    {
        std::string word;
        char nextLetter;
        while (file >> std::noskipws >> nextLetter)
        {
            if (std::isspace(static_cast<unsigned char>(nextLetter)))
            {
                if (!word.empty())
                {
                    words.push_back(word);
                    word = "";
                }
                continue;
            }
            switch (nextLetter)
            {
                case ':':
                    if (words.back() == ":")
                    {
                        words.back() += ':';
                        continue;
                    }
                case '{':
                case '}':
                case '(':
                case ')':
                case '<':
                case '>':
                case ';':
                case '*':
                case ',':
                case '=':
                    if (!word.empty())
                    {
                        words.push_back(word);
                        word = "";
                    }
                    word += nextLetter;
                    words.push_back(word);
                    word = "";
                    break;
                default:
                    word += nextLetter;
            }
        }
        if (!word.empty())
        {
            words.push_back(word);
            word = "";
        }
    }

    void CodeManager::WriteSetOrGetValueFunc(std::ofstream& file, VariableType type, bool writeSetFunc)
    {
        if (writeSetFunc)
        {
            file << "\nextern \"C\" void SetValue" << ToStringUpper(type)
                 << "(const std::string& componentType, const std::string& varName, const Entity& entity, "
                 << ToString(type) << " val) {\n";
        }
        else
        {
            file << "\nextern \"C\" " << ToString(type) << " GetValue" << ToStringUpper(type)
                 << "(const std::string& componentType, const std::string& varName, const Entity& entity) {\n";
        }

        for (const auto& component : components)
        {
            file << "\tif (componentType == \"" << component << "\")\n\t{\n";
            for (const std::pair<VariableType, std::string>& var : componentVariables[component])
            {
                if (var.first != type)
                    continue;
                file << "\t\tif (varName == \"" << var.second << "\")\n";
                if (writeSetFunc)
                {
                    file << "\t\t\t" << component << "::GetComponent(entity)." << var.second << " = val;\n";
                }
                else
                {
                    file << "\t\t\treturn " << component << "::GetComponent(entity)." << var.second << ";\n";
                }
            }

            if (writeSetFunc)
                file << "\t\treturn;\n";
            file << "\t}\n";
        }
        if (!writeSetFunc)
            file << "\treturn " << ToString(type) << "(0);\n";
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
                return "vec2";
            case VariableType::VEC3:
                return "vec3";
            case VariableType::VEC4:
                return "vec4";
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
        }
        return "Error";
    }
}