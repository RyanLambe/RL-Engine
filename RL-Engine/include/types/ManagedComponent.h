#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

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
                ((Core::Entity::Component*)instance)->exists = false;
                //delete instance;
            }
        }
        !ManagedComponent()
        {
            if (instance != nullptr)
            {
                ((Core::Entity::Component*)instance)->exists = false;
                //delete instance;
            }
        }
        T* GetInstance()
        {
            return instance;
        }
    };
}
