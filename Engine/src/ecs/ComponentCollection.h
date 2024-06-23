#pragma once

#include <unordered_map>
#include <memory>
#include "ComponentType.h"

namespace rl {

    class ComponentCollection {
    public:

        template<typename T>
        ComponentType<T>* GetComponentType(){
            if(!typeToComponentType.contains(typeid(T).hash_code())){
                typeToComponentType[typeid(T).hash_code()] = std::make_unique<ComponentType<T>>();
            }
            return (ComponentType<T>*)typeToComponentType[typeid(T).hash_code()].get();
        }

    private:
        /// array of pointers to ComponentType's stored on the heap
        std::unordered_map<size_t, std::unique_ptr<ComponentGroup>> typeToComponentType;
    };
}