#pragma once

#include <unordered_map>

#include "../core/RLResult.h"
#include "../types/OptionalVector.h"

#include "SceneManager.h"

namespace rl {

    template <typename T>
    class Component {
    public:

        Component() = default;

        static inline T& Create(Entity entity)
    	{
            return Scene::MainScene().components.GetComponentType<T>()->Create(entity);
        }

        static RLResult Delete(Entity entity)
    	{
            return Scene::MainScene().components.GetComponentType<T>()->Delete(entity);
        }

        inline static T& GetComponent(Entity entity)
    	{
            return Scene::MainScene().components.GetComponentType<T>()->GetComponent(entity);
        }

        inline static bool HasComponent(Entity entity)
        {
            return Scene::MainScene().components.GetComponentType<T>()->HasComponent(entity);
        }

        inline static OptionalVector<T>& GetAllComponents() noexcept
    	{
            return Scene::MainScene().components.GetComponentType<T>()->GetAllComponents();
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
