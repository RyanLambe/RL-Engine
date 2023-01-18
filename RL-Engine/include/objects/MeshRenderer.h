#pragma once
#include <msclr\marshal_cppstd.h>

#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "../types/ManagedComponent.h"
#include "../types/Material.h"
#include "../types/Mesh.h"

namespace Engine {
	public ref class MeshRenderer : public ManagedComponent<Core::MeshRenderer> {
	public:

		MeshRenderer(Entity^ entity);

		//setters
		void setMaterial(Material^ mat);
		void setMesh(Mesh^ mesh);
		void ImportMeshObj(System::String^ fileName);

		//getters
		Material^ getMaterial();
		Mesh^ getMesh();
	};
}