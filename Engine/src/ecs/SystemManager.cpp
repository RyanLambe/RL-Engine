#include "SystemManager.h"

std::vector<rl::System> rl::SystemManager::systems = std::vector<rl::System>();

void rl::SystemManager::StartSystems() {
    for (auto& system : systems){
        if(system.Start.has_value())
            system.Start.value()();
    }
}

void rl::SystemManager::UpdateSystems() {
    for (auto& system : systems){
        if(system.Update.has_value())
            system.Update.value()();
    }
}
