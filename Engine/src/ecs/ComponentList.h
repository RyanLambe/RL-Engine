#pragma once

#include <vector>
#include <unordered_map>
#include <cstdint>


namespace rl {

    using Entity = uint32_t;

    template <typename T>
    class ComponentList {
    public:

        void Attach(Entity entity, T value){
            if(map.contains(entity))
                return;
        }

        template<typename ... Args>
        void AttachNew(Entity entity, Args&& ... args){

        }

        // removes entities component from list
        void Remove(Entity entity){

        }

        // get component value from
        T* Get(Entity entity){

        }


    private:

        std::vector<T> components = std::vector<T>();
        std::unordered_map<Entity, size_t> map = std::unordered_map<Entity, size_t>();

    };
}
