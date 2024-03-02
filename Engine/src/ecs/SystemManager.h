#pragma once

#include <functional>
#include <optional>

namespace rl{

    struct System {
        std::optional<std::function<void()>> Start;
        std::optional<std::function<void()>> Update;
    };

    class SystemManager {
    public:
        inline static void AddSystem(const System& system) noexcept
        {
            systems.push_back(system);
        }

        static void StartSystems();
        static void UpdateSystems();

    private:
        static std::vector<System> systems;
    };
}