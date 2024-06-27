#pragma once

#include <memory>
#include <string>

#include "glm/glm.hpp"

#include "Key.h"
#include "Axis.h"

namespace rl {

    namespace internal {
        class Input {
        public:
            virtual ~Input() = default;

            [[nodiscard]] virtual float GetKey(Key key) const = 0;
            [[nodiscard]] virtual float GetAxis(const std::string& axis) = 0;
            [[nodiscard]] virtual glm::vec2 GetMousePos() const = 0;

            virtual void CreateAxis(const std::string& key, Axis axis) = 0;
        };
    }

    class Input {
    public:

        [[nodiscard]] static float GetKey(Key key);
        [[nodiscard]] static float GetAxis(const std::string& axis);
        [[nodiscard]] static glm::vec2 GetMousePos();

        static void CreateAxis(const std::string& key, Axis axis);
    };
}

