#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace rl::ed
{
    class CodeManager
    {
    public:
        static void AddSystem(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile);
        static void AddComponent(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile);

        static void Generate();

        float test = 0;

    private:
        static void GenerateCmake();
        static void GenerateSetupCpp();

        static void ParseComponent(const std::string& component);
        static void BreakupHeaderToWords(std::vector<std::string>& words, std::ifstream& file);

        // names of the systems/components
        static std::vector<std::string> systems;
        static std::vector<std::string> components;

        // gets the location of the file based on the name
        static std::unordered_map<std::string, std::string> cppFiles;
        static std::unordered_map<std::string, std::string> headerFiles;
    };
}
