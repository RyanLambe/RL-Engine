#include "../../include/objects/Scene.h"

using namespace Engine;

Scene::Scene() {
	instance = Core::SceneManager::CreateScene();
}

Scene::Scene(Core::SceneManager::Scene* scene) {
	instance = scene;
}

Scene::~Scene() {
	Core::SceneManager::DeleteScene(instance->GetID());
}

int Scene::GetID() {
	if(instance)
		return instance->GetID();
	return -1;
}

void Scene::SetActiveScene() {
	Core::SceneManager::SetActiveScene(instance->GetID());
}

Scene^ Scene::GetActiveScene() {
	return gcnew Scene(Core::SceneManager::GetActiveScene());
}

Scene^ Scene::GetScene(int id) {
	return gcnew Scene(Core::SceneManager::GetScene(id));
}

Entity^ Scene::CreateEntity() {
	return gcnew Entity(instance->CreateEntity());
}

Entity^ Scene::GetEntity(int index) {
	return gcnew Entity(instance->GetEntity(index));
}

void Scene::DeleteEntity(int index) {
	instance->DeleteEntity(index);
}