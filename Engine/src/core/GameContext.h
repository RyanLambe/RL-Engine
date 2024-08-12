#pragma once

#include <utility>

#include "../types/Types.h"
#include "DynamicLibrary.h"

namespace rl
{
    class GameContext
    {
    public:
        GameContext() = delete;
        GameContext(std::shared_ptr<DynamicLibrary> lib) : library(std::move(lib)) {}
        ~GameContext(){
            library = nullptr;
        }

        void Setup();

        void AddSystem(const std::string& system);

        void AddComponent(const std::string& component, Entity entity);
        void RemoveComponent(const std::string& component, Entity entity);
        void* GetComponent(const std::string& component, Entity entity);

        void GetComponentValue(const VariableType& valType, const std::string& componentType,
                               const std::string& varName, const Entity& entity, void* outBuf);

        template<typename T>
        void SetComponentValue(const VariableType& valType, const std::string& componentType,
                               const std::string& varName, const Entity& entity, T val)
        {
            library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity, val);
        }

        void UpdateComponent(const std::string& component, Entity entity);

    private:
        std::shared_ptr<DynamicLibrary> library;
    };
}
