#pragma once

#include <memory>

#include "Key.h"
#include "glm/vec2.hpp"

namespace rl::Input {

    extern void Setup();

    extern bool GetKey(Key key);

    extern bool GetMouseButton(MouseButton button);

    extern glm::vec2 GetMousePos();

}

