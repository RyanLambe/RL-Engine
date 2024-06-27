#pragma once

#include <utility>
#include <vector>

namespace rl
{

    struct Axis
    {
        // array of keys with their weights
        std::vector<std::pair<Key, float>> keys;
    };

} // namespace rl