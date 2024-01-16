#include "SceneManager.h"

using namespace rl;

std::list<SceneManager::Scene> SceneManager::scenes = std::list<SceneManager::Scene>();

int SceneManager::nextId = 0;
int SceneManager::active = -1;

//scene functions
SceneManager::Scene::Scene(int id) {
	this->id = id;
}

int SceneManager::Scene::GetID() {
	return id;
}

Entity* SceneManager::Scene::CreateEntity() {
	entities.emplace_back();
	return &entities.back();
}

Entity* SceneManager::Scene::GetEntity(int index) {
	std::list<Entity>::iterator it = entities.begin();
	std::advance(it, index);
	return &(*it);
}

void SceneManager::Scene::DeleteEntity(int index) {
	std::list<Entity>::iterator it = entities.begin();
	std::advance(it, 2);
	entities.erase(it);
}

//scene manager functions
void SceneManager::SetActiveScene(int id) {
	//todo: disable all entities in old scene
	//todo: enable all entities in new scene
	active = id;
}

SceneManager::Scene* SceneManager::GetActiveScene() {
	return GetScene(active);
}

SceneManager::Scene* SceneManager::CreateScene() {
	if (active == -1)
		active = nextId;

	scenes.emplace_back(nextId++);
	return &scenes.back();
}

SceneManager::Scene* SceneManager::GetScene(int id) {
	for (Scene& scene : scenes)
		if (scene.GetID() == id)
			return &scene;
	return nullptr;
}

void SceneManager::DeleteScene(int id) {
	for (Scene& scene : scenes) {
		if (scene.GetID() == id) {
			std::list<Scene>::iterator it = scenes.begin();
			std::advance(it, 2);
			scenes.erase(it);

			if (id == active && scenes.size() > 0)
				active = scenes.front().GetID();

			return;
		}
	}
		
}