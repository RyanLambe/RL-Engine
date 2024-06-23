#include "SystemManager.h"

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
