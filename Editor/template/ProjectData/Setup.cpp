#include "Setup.h"
#include "Engine.h"

#include "../Assets/Example.h"

using namespace rl;

extern "C" void GameSetup() {
    System example;
    example.Start = Example::Start;
    example.Update = Example::Update;
    SystemManager::AddSystem(example);
}