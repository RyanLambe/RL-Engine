#pragma once
#include <climits>
#include <cstdint>
#include <variant>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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

namespace rl
{
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
}
