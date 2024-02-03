#pragma once

#include <chrono>

namespace rl {
    class Timer {
    public:
        void Start() {
            start = std::chrono::high_resolution_clock::now();
        }

        uint64_t getTime() {
            auto now = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
            return duration.count();
        }

    private:
        std::chrono::high_resolution_clock::time_point start;
    };
}