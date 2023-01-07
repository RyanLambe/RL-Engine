#pragma once
#include "../../pch.h"

#include "../objects/Entity.h"

namespace Engine {

    template<class T>
    public ref class ManagedComponent : public Entity::Component
    {
    protected:
        T* instance;
    public:
        ManagedComponent(T* instance, Entity^ entity)
            : Component(entity), instance(instance)
        {
        }
        virtual ~ManagedComponent()
        {
            if (instance != nullptr)
            {
                delete instance;
            }
        }
        !ManagedComponent()
        {
            if (instance != nullptr)
            {
                delete instance;
            }
        }
        T* GetInstance()
        {
            return instance;
        }
    };
}
