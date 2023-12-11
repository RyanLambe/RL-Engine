#include "SceneManager.h"

std::list<Core::SceneManager::Scene> Core::SceneManager::scenes = std::list<Core::SceneManager::Scene>();

int Core::SceneManager::nextId = 0;
int Core::SceneManager::active = -1;

//scene functions
Core::SceneManager::Scene::Scene(int id) {
	this->id = id;
}

int Core::SceneManager::Scene::GetID() {
	return id;
}

Core::Entity* Core::SceneManager::Scene::CreateEntity() {
	entities.emplace_back();
	return &entities.back();
}

Core::Entity* Core::SceneManager::Scene::GetEntity(int index) {
	std::list<Entity>::iterator it = entities.begin();
	std::advance(it, index);
	return &(*it);
}

void Core::SceneManager::Scene::DeleteEntity(int index) {
	std::list<Entity>::iterator it = entities.begin();
	std::advance(it, 2);
	entities.erase(it);
}

//scene manager functions
void Core::SceneManager::SetActiveScene(int id) {
	//todo: disable all entities in old scene
	//todo: enable all entities in new scene
	active = id;
}

Core::SceneManager::Scene* Core::SceneManager::GetActiveScene() {
	return GetScene(active);
}

Core::SceneManager::Scene* Core::SceneManager::CreateScene() {
	if (active == -1)
		active = nextId;

	scenes.emplace_back(nextId++);
	return &scenes.back();
}

Core::SceneManager::Scene* Core::SceneManager::GetScene(int id) {
	for (Scene& scene : scenes)
		if (scene.GetID() == id)
			return &scene;
	return nullptr;
}

void Core::SceneManager::DeleteScene(int id) {
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