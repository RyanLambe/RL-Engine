#pragma once
#include <d3d11.h>

#include "Entity.h"
#include "Camera.h"
#include "../types/Mesh.h"
#include "../types/Shader.h"
#include "../types/Material.h"

class MeshRenderer : public Entity::Component {

public:

	MeshRenderer(ID3D11Device* device, ID3D11DeviceContext* context, Entity* parent);//set instance vars

	//remove
	
	
	void Draw(ID3D11Device* device, ID3D11DeviceContext* context);
	
	Mesh mesh;

	//setters
	//getters
	Material* getMaterial();

private:

	
	Material material;
	Shader shader;

};