#pragma once

#include <unordered_map>

#include "../core/RLResult.h"
#include "../types/OptionalVector.h"

namespace rl {

    using Entity = size_t;

    template <typename T>
    class Component {
    public:

        Component() = default;

        static T& Create(Entity entity)
    	{
            if(entityToIndex.contains(entity)){
                RL_THROW_EXCEPTION("Multiple components cannot be added to the same entity.");
            }

            for (size_t i = 0; i < components.size(); i++) {
                if (components[i] == std::nullopt) {
                    entityToIndex[entity] = i;
                    components[i] = T();
                    components[i].value().entity = entity;
                    return components[i].value();
                }
            }

            components.push_back(T());
            size_t index = components.size() - 1;

            components[index].value().entity = entity;
            entityToIndex[entity] = index;
            return components[index].value();
        }

        static RLResult Delete(Entity entity)
    	{
            if(!entityToIndex.contains(entity))
                return RLResult(ErrorCode::InvalidArguments);
            if(!components[entityToIndex[entity]].has_value())
                return RLResult(ErrorCode::InvalidArguments);

            components[entityToIndex[entity]].reset();
            entityToIndex.erase(entity);

            return RLResult(ErrorCode::Success);
        }

        inline static T& GetComponent(Entity entity)
    	{
            return components[entityToIndex[entity]].value();
        }

        inline static bool HasComponent(Entity entity)
        {
            return entityToIndex.contains(entity);
        }

        inline static OptionalVector<T>& GetAllComponents() noexcept
    	{
            return components;
        }

        [[nodiscard]]
        inline Entity getEntity() const noexcept
        {
            return entity;
        }

    private:
        static std::unordered_map<Entity, size_t> entityToIndex;
        static OptionalVector<T> components;
        Entity entity;
    };

    template<typename T>
    std::unordered_map<Entity, size_t> Component<T>::entityToIndex;

    template<typename T>
    OptionalVector<T> Component<T>::components = OptionalVector<T>();
    
}
