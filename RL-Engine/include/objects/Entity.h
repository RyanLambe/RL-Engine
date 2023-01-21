#pragma once
#include <typeinfo>
#include <msclr\marshal_cppstd.h>

#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif
#include "../types/Transform.h"

namespace Engine {
	public ref class Entity
	{
	private:
		Core::Entity* instance;

	public:
		//component
		ref class Component {
		public:
			Component(Entity^ entity);//create new component
			Component(Core::Entity::Component* comp);
			~Component();
			!Component();

			Entity^ entity = nullptr;
			Transform^ transform = nullptr;

			void SetEntity(Entity^ newEntity);

			template<typename T>
			T* GetInstance() { return (T*)instance; }
			Core::Entity::Component* GetInstance();
		private:
			void CleanUp();
		protected:
			void* instance = nullptr;
			bool instanceOnHeap;
		};

		//general
		Entity(Core::Entity* entity);
		Transform^ transform;
		Core::Entity* GetInstance() { return instance; }

		//component management
		//add component
		void addComponent(Component^ component) {
			component->SetEntity(this);
		}

		//get components
		generic<typename T>
		Component^ getComponent() {
			Core::Entity::Component* component = instance->getComponent(msclr::interop::marshal_as<std::string>(T::typeid->Name));
			if (component == nullptr)
				return nullptr;
			return gcnew Component(component);
		}
		generic<typename T>
		array<Component^>^ getComponents() {
			std::vector<Core::Entity::Component*> in = instance->getComponents(msclr::interop::marshal_as<std::string>(T::typeid->Name));
			if (in.size() == 0)
				return nullptr;
			array<Component^>^ out = gcnew array<Component^>(in.size());
			for(int i = 0; i < in.size(); i++)
				out[i] = gcnew Component(in[i]);
			return out;
		}

		//remove components
		generic<typename T>
		Component^ removeComponent() {
			Core::Entity::Component* component = instance->removeComponent(msclr::interop::marshal_as<std::string>(T::typeid->Name));
			if (component == nullptr)
				return nullptr;
			return gcnew Component(component);
		}
		generic<typename T>
		array<Component^>^ removeComponents() {
			std::vector<Core::Entity::Component*> in = instance->removeComponents(msclr::interop::marshal_as<std::string>(T::typeid->Name));
			if (in.size() == 0)
				return nullptr;
			array<Component^>^ out = gcnew array<Component^>(in.size());
			for (int i = 0; i < in.size(); i++)
				out[i] = gcnew Component(in[i]);
			return out;
		}

		//tree management
		Entity^ getParent();
		void setParent(Entity^ parent);

		int getChildCount();
		Entity^ getChild(int index);
		array<Entity^>^ getChildren();
	};
}


