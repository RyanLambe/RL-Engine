#pragma once

#include <unordered_map>

#include "../core/RLResult.h"
#include "../types/OptionalVector.h"
#include "ComponentCollection.h"

namespace rl
{

    namespace internal
    {
        class ComponentHelper
        {
        public:
            static ComponentCollection& FindActiveComponentCollection();
        };
    } // namespace internal

    template<typename T> class Component
    {
    public:
        Component() = default;

        static inline T& Create(Entity entity)
        {
            return internal::ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->Create(entity);
        }

        static RLResult Delete(Entity entity)
        {
            return internal::ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->Delete(entity);
        }

        inline static T& GetComponent(Entity entity)
        {
            return internal::ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->GetComponent(
                entity);
        }

        inline static bool HasComponent(Entity entity)
        {
            return internal::ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->HasComponent(
                entity);
        }

        inline static OptionalVector<T>& GetAllComponents() noexcept
        {
            return internal::ComponentHelper::FindActiveComponentCollection().GetComponentType<T>()->GetAllComponents();
        }

        [[nodiscard]] inline Entity GetEntity() const noexcept
        {
            return entity;
        }

        inline void setEntity(Entity newEntity) noexcept
        {
            entity = newEntity;
        }

    protected:
        Entity entity;
    };
}
