#include "Scene.h"

#include <fstream>

#include "../core/Application.h"

namespace rl
{
    Scene::Scene(const std::filesystem::path& location) : location(location), name(location.stem().string())
    {
        entities[NullEntity] = EntityData(NullEntity);
        entities[NullEntity].name = "Scene";
    }

    Scene& Scene::GetScene()
    {
        return Application::GetSceneManager().GetCurrentScene();
    }

    Entity Scene::CreateEntity()
    {
        Entity id;
        if (deletedEntities.empty())
        {
            id = nextEntity;
            nextEntity++;
        }
        else
        {
            id = deletedEntities.front();
            deletedEntities.pop_front();
        }
        entities[id] = EntityData(id);
        entities[NullEntity].children.push_back(id);
        return id;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        if (entity == NullEntity || !entities.contains(entity))
        {
            RL_LOG_ERROR("Cannot delete Entity ", entity, " as it does not exist");
        }

        std::vector<Entity> children = GetChildren(entity);
        for (Entity child : children)
        {
            GetEntityData(child)->parent = GetEntityData(entity)->parent;
            GetEntityData(GetEntityData(entity)->parent)->children.push_back(child);
        }

        RemoveEntityFromParentsChildList(entity);
        entities.erase(entity);
        deletedEntities.push_back(entity);
    }

    void Scene::SetParent(Entity parent, Entity child)
    {
        EntityData* childData = GetEntityData(child);
        if (!childData)
        {
            RL_LOG_ERROR("Cannot set parent of Entity ", child, " as it does not exist");
            return;
        }

        RemoveEntityFromParentsChildList(child);
        childData->parent = parent;

        EntityData* parentData = GetEntityData(parent);
        if (parentData)
        {
            parentData->children.push_back(child);
        }
    }

    void Scene::RemoveEntityFromParentsChildList(Entity entity)
    {
        EntityData* data = GetEntityData(entity);
        if (!data)
        {
            RL_LOG_ERROR("Cannot find Entity ", entity);
            return;
        }

        EntityData* parentData = GetEntityData(data->parent);
        if (!parentData)
            return;

        for (int i = 0; i < parentData->children.size(); i++)
        {
            if (GetEntityData(parentData->children[i])->id == entity)
            {
                parentData->children.erase(parentData->children.begin() + i);
                break;
            }
        }
    }

    void Scene::SaveToFile()
    {
        std::ofstream file(location);
        if (!file.is_open())
        {
            RL_LOG_ERROR("Unable to open file: ", location.string());
            return;
        }
        json data = {};

        data["nextEntity"] = nextEntity;
        data["deletedEntities"] = deletedEntities;
        data["entities"] = entities;

        file << std::setw(4) << data << "\n";
    }

    void Scene::LoadFromFile(Scene* scene, const std::filesystem::path& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            RL_LOG_ERROR("Unable to open file: ", filePath.string());
            return;
        }
        json data = json::parse(file);

        scene->nextEntity = data["nextEntity"];
        scene->deletedEntities = data["deletedEntities"].get<std::deque<Entity>>();
        scene->entities = data["entities"].get<std::unordered_map<Entity, EntityData>>();

        scene->LoadComponents();
    }

    void Scene::LoadComponents()
    {
        if (!Application::isGameContextCreated())
        {
            RL_LOG_ERROR("Unable to load scene components as the game context has not been compiled/loaded");
            return;
        }

        // set as active scene
        std::string currentScene;
        if(Application::GetSceneManager().IsSceneOpen())
            currentScene = Application::GetSceneManager().GetCurrentScene().name;
        else
            currentScene = name;
        Application::GetSceneManager().SetScene(name);

        // create components
        for (const auto& entity : entities)
        {
            for (const auto& component : entity.second.componentOrder)
            {
                Application::GetGameContext().AddComponent(component, entity.first);
                Application::GetGameContext().UpdateComponentWithSceneData(component, entity.first);
            }
        }

        // set active scene back
        Application::GetSceneManager().SetScene(currentScene);
    }

    void Scene::InitComponentData(const std::string& componentName,
                                  const std::vector<std::pair<VariableType, std::string>> &values, Entity entity)
    {
        entities[entity].componentOrder.push_back(componentName);
        entities[entity].componentData[componentName] = {};
        for(const auto& value : values){
            entities[entity].componentData[componentName][value.second] = Variable();
            entities[entity].componentData[componentName][value.second].type = value.first;
        }
    }
}