#pragma once

namespace Engine {
    public ref class Debug
    {
    protected:
        int* instance;
    public:
        Debug(int* instance)
            : instance(instance)
        {
        }
        virtual ~Debug()
        {
            if (instance != nullptr)
            {
                delete instance;
            }
        }
        !Debug()
        {
            if (instance != nullptr)
            {
                delete instance;
            }
        }
        int* GetInstance()
        {
            return instance;
        }
    };
}


