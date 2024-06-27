#include "Component.h"

#include "../core/Application.h"

namespace rl::internal
{
    ComponentCollection& ComponentHelper::FindActiveComponentCollection()
    {
        return Application::GetScene().components;
    }
} // namespace rl::internal