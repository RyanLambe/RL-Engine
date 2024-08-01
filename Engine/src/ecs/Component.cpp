#include "Component.h"

#include "../core/Application.h"

namespace rl::internal
{
    ComponentCollection& ComponentHelper::FindActiveComponentCollection()
    {
        return Scene::GetScene().components;
    }
}