#pragma once
#include <d3d11.h>

#include "Entity.h"
#include "Camera.h"
#include "../types/Mesh.h"
#include "../types/Shader.h"
#include "../types/Material.h"

namespace Core {
	class MeshRenderer : public Entity::Component {

	public:

		MeshRenderer(Entity* parent);
		void Draw(ID3D11Device* device, ID3D11DeviceContext* context);

		//setters
		void setMaterial(Material mat);
		void setMesh(Mesh mesh);

		//getters
		Material* getMaterial();
		Mesh* getMesh();

	private:

		Mesh mesh;
		Material material;

	};
}