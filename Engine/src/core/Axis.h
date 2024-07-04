#pragma once

#include <utility>
#include <vector>

#include "Key.h"

namespace rl
{

    struct Axis
    {
        // array of keys with their weights
        std::vector<std::pair<Key, float>> keys;
    };

}