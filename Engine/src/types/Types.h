#pragma once
#include <climits>
#include <cstdint>
#include <glm/glm.hpp>

// vectors
using quaternion = glm::quat;
using vec4 = glm::vec4;
using vec3 = glm::vec3;
using vec2 = glm::vec2;

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
