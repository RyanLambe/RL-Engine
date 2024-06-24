#include "Component.h"

#include "../core/Application.h"

namespace rl
{
    ComponentCollection& ComponentHelper::FindActiveComponentCollection() {
        return Application::GetScene().components;
    }
}