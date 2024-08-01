#pragma once

#include <memory>
#include <vector>

#include "../core/Logger.h"
#include "../types/Types.h"

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

        template<typename T> inline void AddSystem(const std::string& name) noexcept
        {
            static_assert(std::is_base_of<System, T>::value, "T must inherit from System");
            systems.emplace_back(true, std::make_unique<T>());
            names.push_back(name);
        }

        [[nodiscard]] inline size_t GetSystemsCount() const
        {
            return systems.size();
        }

        [[nodiscard]] inline const std::string& GetName(i64 index) const
        {
            return names[index];
        }

        [[nodiscard]] inline bool* GetEnabledPtr(i64 index)
        {
            return &systems[index].first;
        }

        inline void SwapSystems(i64 a, i64 b)
        {
            std::iter_swap(systems.begin() + a, systems.begin() + b);
            std::iter_swap(names.begin() + a, names.begin() + b);
        }

        inline void RemoveSystem(i64 index)
        {
            systems.erase(systems.begin() + index);
            names.erase(names.begin() + index);
        }

        inline void RemoveAllSystems()
        {
            systems = std::vector<std::pair<bool, std::unique_ptr<System>>>();
        }

        void StartSystems();
        void UpdateSystems();

    private:
        std::vector<std::pair<bool, std::unique_ptr<System>>> systems = {};
        std::vector<std::string> names = {};
    };
}