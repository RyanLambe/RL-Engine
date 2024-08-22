#include "SystemManager.h"

#include "../core/Application.h"
#include "../systems/Renderer.h"

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

void rl::SystemManager::LoadJSON(const json& j)
{
    RemoveAllSystems();
    if (!Application::isGameContextCreated())
    {
        RL_LOG_ERROR("Unable to load systems from file as the game context has not been created/set.");
        return;
    }

    // assumption: this == set scene (can be temporary for loading purposes)
    std::vector<std::pair<bool, std::string>> input;
    input = j["systems"];
    for (const auto& sys : input)
    {
        Application::GetGameContext().AddSystem(sys.second);
        systems.back().first = sys.first;
    }
}
