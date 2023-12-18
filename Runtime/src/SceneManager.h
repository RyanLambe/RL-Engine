#pragma once
#include <list>
#include "objects/Entity.h"

namespace rl {

	static class SceneManager {
	public:

		class Scene {
		public:
			Scene(int id);
			int GetID();

			Entity* CreateEntity();
			Entity* GetEntity(int index);
			void DeleteEntity(int index);

		private:
			std::list<Entity> entities = std::list<Entity>();
			int id;
		};

		static void SetActiveScene(int id);
		static Scene* GetActiveScene();

		static Scene* CreateScene();
		static Scene* GetScene(int id);
		static void DeleteScene(int id);

	private:
		static std::list<Scene> scenes;

		static int nextId;
		static int active;
	};

}