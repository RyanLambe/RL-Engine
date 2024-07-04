#pragma once

#include <unordered_map>

#include "../core/RLResult.h"
#include "../types/OptionalVector.h"

namespace rl
{

    using Entity = size_t;

    namespace internal
    {
        class ComponentType
        {};
    }

    template<typename T> class ComponentType : public internal::ComponentType
    {
    public:
        ComponentType() = default;

        T& Create(Entity entity)
        {
            if (entityToIndex.contains(entity))
            {
                RL_THROW_EXCEPTION("Multiple components cannot be added to the same entity.");
            }

            for (size_t i = 0; i < components.size(); i++)
            {
                if (components[i] == std::nullopt)
                {
                    entityToIndex[entity] = i;
                    components[i] = T();
                    components[i].value().setEntity(entity);
                    return components[i].value();
                }
            }

            components.push_back(T());
            size_t index = components.size() - 1;

            components[index].value().setEntity(entity);
            entityToIndex[entity] = index;
            return components[index].value();
        }

        RLResult Delete(Entity entity)
        {
            if (!entityToIndex.contains(entity))
                return RLResult(ErrorCode::InvalidArguments);
            if (!components[entityToIndex[entity]].has_value())
                return RLResult(ErrorCode::InvalidArguments);

            components[entityToIndex[entity]].reset();
            entityToIndex.erase(entity);

            return RLResult(ErrorCode::Success);
        }

        T& GetComponent(Entity entity)
        {
            return components[entityToIndex[entity]].value();
        }

        bool HasComponent(Entity entity)
        {
            return entityToIndex.contains(entity);
        }

        OptionalVector<T>& GetAllComponents() noexcept
        {
            return components;
        }

    private:
        std::unordered_map<Entity, size_t> entityToIndex = {};
        OptionalVector<T> components = OptionalVector<T>();
    };
}