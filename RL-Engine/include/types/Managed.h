#pragma once

namespace Engine {

    template<class T>
    public ref class Managed
    {
    protected:
        T* instance;
    public:
        Managed(T* instance)
            : instance(instance)
        {
        }
        virtual ~Managed()
        {
            if (instance != nullptr)
            {
                delete instance;
            }
        }
        !Managed()
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
