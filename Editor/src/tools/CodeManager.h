#pragma once

#include <types/Types.h>

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include "../project/ProjectManager.h"
#include "ecs/ComponentType.h"

namespace rl::ed
{
    class CodeManager
    {
    public:
        static void AddSystem(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile);
        static void AddComponent(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile);

        static void AddBuiltInSystem(const std::filesystem::path& headerFile);
        static void AddBuiltInComponent(const std::filesystem::path& headerFile);

        static const std::vector<std::string>& GetSystems();
        static const std::vector<std::string>& GetComponents();

        static const std::vector<std::pair<VariableType, std::string>>& GetProperties(const std::string& component);

        static void Generate();

    private:
        static void GenerateCmake();
        static void GenerateSetupCpp();
        static void GenerateSetupHeader();

        static void ParseComponent(const std::string& component);

        static void WriteAddSystemFunc(std::ofstream& file);

        static void WriteSetOrGetValueFunc(std::ofstream& file, VariableType type, bool writeSetFunc);
        static void WriteAddOrRemoveComponentFunc(std::ofstream& file, bool writeAddFunc);
        static void WriteGetComponentFunc(std::ofstream& file);

        // names of the systems/components
        static std::vector<std::string> systems;
        static std::vector<std::string> components;

        // gets the location of the file based on the name
        static std::unordered_map<std::string, std::string> cppFiles;
        static std::unordered_map<std::string, std::string> headerFiles;
        static std::unordered_map<std::string, std::string> builtInFiles;

        static std::unordered_map<std::string, std::vector<std::pair<VariableType, std::string>>> componentVariables;
    };
}
