#pragma once

#include <vector>
#include <utility>

namespace rl {

    struct Axis {
        // array of keys with their weights
        std::vector<std::pair<Key, float>> keys;
    };

}