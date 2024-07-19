#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>

namespace rl::ed {
    class CodeManager {
    public:

        static void AddSystem(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile);
        static void AddComponent(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile);

        static void Generate();

    private:

        static void GenerateCmake();
        static void GenerateSetupCpp();

        // names of the systems/components
        static std::vector<std::string> systems;
        static std::vector<std::string> components;

        // gets the location of the file based on the name
        static std::unordered_map<std::string, std::string> cppFiles;
        static std::unordered_map<std::string, std::string> headerFiles;
    };
}
