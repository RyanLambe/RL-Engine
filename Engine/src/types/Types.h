#pragma once

#include <climits>
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <variant>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// floats
static_assert(sizeof(double) * CHAR_BIT == 64, "double is not 64 bit on this architecture, fix the f64 typedef.");
using f64 = double;

static_assert(sizeof(float) * CHAR_BIT == 32, "float is not 32 bit on this architecture, fix the f32 typedef.");
using f32 = float;

// unsigned ints
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

// ints
using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;

// entity
namespace rl
{
    using Entity = size_t;
    const Entity NullEntity = Entity(0);
}

// vectors
using Quaternion = glm::quat;
using Vec4 = glm::vec4;
using Vec3 = glm::vec3;
using Vec2 = glm::vec2;

namespace glm
{
    static void to_json(json& j, const Quaternion& val)
    {
        j["x"] = val.x;
        j["y"] = val.y;
        j["z"] = val.z;
        j["w"] = val.w;
    }
    static void from_json(const json& j, Quaternion& val)
    {
        val.x = j["x"];
        val.y = j["y"];
        val.z = j["z"];
        val.w = j["w"];
    }

    static void to_json(json& j, const Vec4& val)
    {
        j["x"] = val.x;
        j["y"] = val.y;
        j["z"] = val.z;
        j["w"] = val.w;
    }
    static void from_json(const json& j, Vec4& val)
    {
        val.x = j["x"];
        val.y = j["y"];
        val.z = j["z"];
        val.w = j["w"];
    }

    static void to_json(json& j, const Vec3& val)
    {
        j["x"] = val.x;
        j["y"] = val.y;
        j["z"] = val.z;
    }
    static void from_json(const json& j, Vec3& val)
    {
        val.x = j["x"];
        val.y = j["y"];
        val.z = j["z"];
    }

    static void to_json(json& j, const Vec2& val)
    {
        j["x"] = val.x;
        j["y"] = val.y;
    }
    static void from_json(const json& j, Vec2& val)
    {
        val.x = j["x"];
        val.y = j["y"];
    }
}

namespace rl
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

    struct Variable
    {
        VariableData data;
        VariableType type;
    };

    static std::string ToString(VariableType type)
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

    static std::string ToStringUpper(VariableType type)
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

    static void from_json(const json& j, Variable& val)
    {
        val.type = j["type"];
        switch (val.type)
        {
            case VariableType::I8:
                val.data.I8 = j["data"];
                return;
            case VariableType::I16:
                val.data.I16 = j["data"];
                return;
            case VariableType::I32:
                val.data.I32 = j["data"];
                return;
            case VariableType::I64:
                val.data.I64 = j["data"];
                return;
            case VariableType::U8:
                val.data.U8 = j["data"];
                return;
            case VariableType::U16:
                val.data.U16 = j["data"];
                return;
            case VariableType::U32:
                val.data.U32 = j["data"];
                return;
            case VariableType::U64:
                val.data.U64 = j["data"];
                return;
            case VariableType::F32:
                val.data.F32 = j["data"];
                return;
            case VariableType::F64:
                val.data.F64 = j["data"];
                return;
            case VariableType::VEC2:
                val.data.Vec2 = j["data"];
                return;
            case VariableType::VEC3:
                val.data.Vec3 = j["data"];
                return;
                return;
            case VariableType::VEC4:
                val.data.Vec4 = j["data"];
                return;
            case VariableType::QUAT:
                val.data.Quat = j["data"];
                return;
            default:
                return;
        }
    }

    static void to_json(json& j, const Variable& val)
    {
        j["type"] = val.type;
        switch (val.type)
        {
            case VariableType::I8:
                j["data"] = val.data.I8;
                return;
            case VariableType::I16:
                j["data"] = val.data.I16;
                return;
            case VariableType::I32:
                j["data"] = val.data.I32;
                return;
            case VariableType::I64:
                j["data"] = val.data.I64;
                return;
            case VariableType::U8:
                j["data"] = val.data.U8;
                return;
            case VariableType::U16:
                j["data"] = val.data.U16;
                return;
            case VariableType::U32:
                j["data"] = val.data.U32;
                return;
            case VariableType::U64:
                j["data"] = val.data.U64;
                return;
            case VariableType::F32:
                j["data"] = val.data.F32;
                return;
            case VariableType::F64:
                j["data"] = val.data.F64;
                return;
            case VariableType::VEC2:
                j["data"] = val.data.Vec2;
                return;
            case VariableType::VEC3:
                j["data"] = val.data.Vec3;
                return;
            case VariableType::VEC4:
                j["data"] = val.data.Vec4;
                return;
            case VariableType::QUAT:
                j["data"] = val.data.Quat;
                return;
            default:
                return;
        }
    }
}
