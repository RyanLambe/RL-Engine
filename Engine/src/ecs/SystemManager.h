#pragma once

#include <vector>
#include <memory>

namespace rl{

    class System
    {
    public:
        virtual ~System() = default;
        virtual void Start() = 0;
        virtual void Update() = 0;
    };

    class SystemManager {
    public:
        SystemManager() = default;

        template <typename T>
        void AddSystem() noexcept
        {
            static_assert(std::is_base_of<System, T>::value, "T must inherit from System");
            systems.push_back(std::make_unique<T>());
        }

        void StartSystems();
        void UpdateSystems();

    private:
        std::vector<std::unique_ptr<System>> systems = std::vector<std::unique_ptr<System>>();
    };
}