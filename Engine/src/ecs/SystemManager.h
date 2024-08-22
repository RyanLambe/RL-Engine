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

        template<typename T> inline void AddSystem(const std::string& name)
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

        [[nodiscard]] inline bool IsEnabled(i64 index) const
        {
            return systems[index].first;
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
            names = {};
        }

        void StartSystems();
        void UpdateSystems();

        void LoadJSON(const json& j);

    private:
        std::vector<std::pair<bool, std::unique_ptr<System>>> systems = {};
        std::vector<std::string> names = {};
    };

    static void to_json(json& j, const SystemManager& val)
    {
        std::vector<std::pair<bool, std::string>> systems;
        for(int i = 0; i < val.GetSystemsCount(); i++){
            systems.emplace_back(val.IsEnabled(i), val.GetName(i));
        }
        j["systems"] = systems;
    }
}