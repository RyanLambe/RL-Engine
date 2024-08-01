#include "SystemManager.h"

void rl::SystemManager::StartSystems()
{
    for (auto& system : systems)
    {
        try
        {
            if (system.first)
                system.second->Start();
        }
        catch (const std::exception& e)
        {
            RL_LOG_ERROR(e.what());
        }
        catch (...)
        {
            RL_LOG_ERROR("Caught Unknown Exception");
        }
    }
}

void rl::SystemManager::UpdateSystems()
{
    for (auto& system : systems)
    {
        try
        {
            if (system.first)
                system.second->Update();
        }
        catch (const std::exception& e)
        {
            RL_LOG_ERROR(e.what());
        }
        catch (...)
        {
            RL_LOG_ERROR("Caught Unknown Exception");
        }
    }
}
