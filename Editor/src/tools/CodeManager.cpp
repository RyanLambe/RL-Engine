#include "CodeManager.h"

#include "../project/ProjectManager.h"
#include "core/Logger.h"
#include "fstream"

namespace rl::ed
{
    std::vector<std::string> CodeManager::systems = {};
    std::vector<std::string> CodeManager::components = {};

    std::unordered_map<std::string, std::string> CodeManager::cppFiles = {};
    std::unordered_map<std::string, std::string> CodeManager::headerFiles = {};

    std::unordered_map<std::string, std::vector<std::pair<VariableType, std::string>>> CodeManager::componentVariables = {};

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

    void CodeManager::Generate()
    {
        GenerateCmake();
        GenerateSetupCpp();
        for (const auto& component : components)
        {
            ParseComponent(component);
        }
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
             << "void GameSetupInternal(void* mainApp){\n"
                "\tApplication::ConnectToApp((std::shared_ptr<Application>*)mainApp);\n\n";

        // todo: find better way to add systems that is linked to the scene
        file << "\tApplication::GetScene().systemManager.AddSystem<Renderer>();\n";
        for (const auto& system : systems)
        {
            file << "\tApplication::GetScene().systemManager.AddSystem<" << system << ">();\n";
        }
        file << "}\n";

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
                while (i + 3 < words.size() && words[i] != "{")
                {
                    if (words[i] == "public" && words[i + 1] == "rl" && words[i + 2] == "::"
                        && words[i + 3] == "Component")
                    {
                        classDef = true;
                        goalBracketsDeep = bracketsDeep + 1;
                        i += 3;
                        break;
                    }
                    i++;
                }
                if (!classDef)
                {
                    RL_LOG_ERROR(component, " must inherit from the \"rl::Component\" class.");
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
                std::string temp = words[i + 2];
                if (temp != ";" && temp != "=") // name followed by
                    continue;

                if (words[i] == "float")
                {
                    if(!componentVariables.contains(component))
                        componentVariables[component] = {};
                    componentVariables[component].emplace_back(VariableType::F32, words[i + 1]);
                    RL_LOG("float at: ", words[i + 1]);
                }

                if (words[i] == "double")
                {
                    if(!componentVariables.contains(component))
                        componentVariables[component] = {};
                    componentVariables[component].emplace_back(VariableType::F64, words[i + 1]);
                    RL_LOG("double at: ", words[i + 1]);
                }

                if (words[i] == "int")
                {
                    if(!componentVariables.contains(component))
                        componentVariables[component] = {};
                    componentVariables[component].emplace_back(VariableType::I32, words[i + 1]);
                    RL_LOG("int at: ", words[i + 1]);
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
}