#include "SceneManager.h"

#include "../core/Application.h"

using namespace rl;

Scene &Scene::MainScene()
{
    return Application::GetScene();
}
