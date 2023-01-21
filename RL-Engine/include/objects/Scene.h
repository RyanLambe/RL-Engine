#pragma once

#include "../../../RL-EngineCore/include/SceneManager.h"
#include "Entity.h"

namespace Engine {

	public ref class Scene {

	public:
		Scene();
		Scene(Core::SceneManager::Scene* scene);
		~Scene();

		int GetID();

		void SetActiveScene();
		static Scene^ GetActiveScene();
		static Scene^ GetScene(int id);

		Entity^ CreateEntity();
		Entity^ GetEntity(int index);
		void DeleteEntity(int index);

	private:
		Core::SceneManager::Scene* instance;
	};

}
