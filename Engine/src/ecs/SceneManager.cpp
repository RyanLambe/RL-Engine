#include "SceneManager.h"

#include "../core/Application.h"

using namespace rl;

Scene& Scene::MainScene()
{
    return Application::GetScene();
}

Entity Scene::CreateEntity()
{
    Entity temp;
    if (deletedEntities.empty())
    {
        temp = nextEntity;
        nextEntity++;
    }
    else
    {
        temp = deletedEntities.front();
        deletedEntities.pop();
    }
    entities.push_back(temp);
    return temp;
}

void Scene::DestroyEntity(Entity entity)
{
    deletedEntities.push(entity);
    entities.erase(std::remove(entities.begin(), entities.end(), 8), entities.end());
}
