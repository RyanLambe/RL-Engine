#pragma once
#include <msclr\marshal_cppstd.h>

#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "Entity.h"

#include "../types/Material.h"
#include "../types/Mesh.h"

namespace Engine {
	public ref class MeshRenderer : public Entity::Component
	{
	public:
		MeshRenderer();
		MeshRenderer(Entity^ entity);
		MeshRenderer(Core::MeshRenderer* mesh);

		static MeshRenderer^ CastAs(Entity::Component^ component);

		//setters
		void setMaterial(Material^ mat);
		void setMesh(Mesh^ mesh);
		void ImportMeshObj(System::String^ fileName);

		//getters
		Material^ getMaterial();
		Mesh^ getMesh();
	};
}