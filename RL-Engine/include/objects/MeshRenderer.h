#pragma once
#include "../../pch.h"

#include <msclr\marshal_cppstd.h>

#include "../types/ManagedComponent.h"
#include "../types/Material.h"
#include "../types/Mesh.h"

namespace Engine {
	public ref class MeshRenderer : public ManagedComponent<Core::MeshRenderer> {
	public:

		MeshRenderer(ID3D11Device* device, ID3D11DeviceContext* context, Entity^ entity);

		//setters
		void setMaterial(Material^ mat);
		void setMesh(Mesh^ mesh);

		//getters
		Material^ getMaterial();
		Mesh^ getMesh();
	};
}