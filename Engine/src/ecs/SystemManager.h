#pragma once

#include <memory>
#include <vector>

#include "../core/Logger.h"

namespace rl
{

    class System
    {
    public:
        virtual ~System() = default;
        virtual void Start() = 0;
        virtual void Update() = 0;
    };

    class SystemManager
    {
    public:
        SystemManager() = default;

        template<typename T> inline void AddSystem() noexcept
        {
            static_assert(std::is_base_of<System, T>::value, "T must inherit from System");
            systems.push_back(std::make_unique<T>());
        }

        inline void RemoveAllSystems()
        {
            systems = std::vector<std::unique_ptr<System>>();
        }

        void StartSystems();
        void UpdateSystems();

    private:
        std::vector<std::unique_ptr<System>> systems = std::vector<std::unique_ptr<System>>();
    };
}