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
        SystemManager() = default;

        inline void AddSystem(const System& system) noexcept
        {
            systems.push_back(system);
        }

        void StartSystems();
        void UpdateSystems();

    private:
        std::vector<System> systems = std::vector<rl::System>();
    };
}