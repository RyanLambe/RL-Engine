#include "SystemManager.h"

void rl::SystemManager::StartSystems()
{
    for (auto& system : systems)
    {
        system->Start();
    }
}

void rl::SystemManager::UpdateSystems()
{
    for (auto& system : systems)
    {
        system->Update();
    }
}
