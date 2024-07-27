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
    enum class VariableType : uint8_t
    {
        Unknown = 0,
        I8 = 1,
        I16 = 2,
        I32 = 3,
        I64 = 4,
        U8 = 5,
        U16 = 6,
        U32 = 7,
        U64 = 8,
        F32 = 9,
        F64 = 10,
        VEC2 = 11,
        VEC3 = 12,
        VEC4 = 13,
        QUAT = 14,
    };

    union VariableData {
        i8 I8;
        i16 I16;
        i32 I32;
        i64 I64;
        u8 U8;
        u16 U16;
        u32 U32;
        u64 U64;
        f32 F32;
        f64 F64;
        Vec2 Vec2;
        Vec3 Vec3;
        Vec4 Vec4;
        Quaternion Quat;
    };

    class CodeManager
    {
    public:
        static void AddSystem(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile);
        static void AddComponent(const std::filesystem::path& cppFile, const std::filesystem::path& headerFile);

        static void AddBuiltInSystem(const std::filesystem::path& headerFile);
        static void AddBuiltInComponent(const std::filesystem::path& headerFile);

        static const std::vector<std::string>& GetSystems();
        static const std::vector<std::string>& GetComponents();

        static void AddSystem(const std::string& system);

        static const std::vector<std::pair<VariableType, std::string>>& GetProperties(const std::string& component);
        static void AddComponent(const std::string& component, rl::Entity entity);
        static void RemoveComponent(const std::string& component, rl::Entity entity);
        static void* GetComponent(const std::string& component, rl::Entity entity);

        static void GetComponentValue(const VariableType& valType, const std::string& componentType,
                                      const std::string& varName, const Entity& entity, void* outBuf);
        template<typename T>
        static void SetComponentValue(const VariableType& valType, const std::string& componentType,
                                      const std::string& varName, const Entity& entity, T val)
        {
            ProjectManager::RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity, val);
        }

        static void Generate();

        float test = 0;

    private:
        static void GenerateCmake();
        static void GenerateSetupCpp();
        static void GenerateSetupHeader();

        static void ParseComponent(const std::string& component);

        static void WriteAddSystemFunc(std::ofstream& file);

        static void WriteSetOrGetValueFunc(std::ofstream& file, VariableType type, bool writeSetFunc);
        static void WriteAddOrRemoveComponentFunc(std::ofstream& file, bool writeAddFunc);
        static void WriteGetComponentFunc(std::ofstream& file);

        static std::string ToString(VariableType type);
        static std::string ToStringUpper(VariableType type);

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
