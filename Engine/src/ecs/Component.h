#pragma once

#include <unordered_map>

#include "ComponentCollection.h"
#include "../types/OptionalVector.h"
#include "../core/RLResult.h"

namespace rl {

    class ComponentHelper {
    public:
        static ComponentCollection& FindActiveComponentCollection();
    };

    template <typename T>
    class Component {
    public:

        Component() = default;

        static inline T& Create(Entity entity)
    	{
            return ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->Create(entity);
        }

        static RLResult Delete(Entity entity)
    	{
            return ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->Delete(entity);
        }

        inline static T& GetComponent(Entity entity)
    	{
            return ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->GetComponent(entity);
        }

        inline static bool HasComponent(Entity entity)
        {
            return ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->HasComponent(entity);
        }

        inline static OptionalVector<T>& GetAllComponents() noexcept
    	{
            return ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->GetAllComponents();
        }

        [[nodiscard]]
        inline Entity getEntity() const noexcept
        {
            return entity;
        }

        inline void setEntity(Entity newEntity) noexcept{
            entity = newEntity;
        }

    protected:
        Entity entity;
    };
}
