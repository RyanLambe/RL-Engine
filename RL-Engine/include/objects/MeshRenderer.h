#pragma once
#include <d3d11.h>

#include "Entity.h"
#include "../types/Mesh.h"
#include "../types/Shader.h"

class MeshRenderer : public Entity::Component {

public:

	MeshRenderer(ID3D11Device* device, ID3D11DeviceContext* context);//set instance vars

	//remove
	
	
	void Draw(ID3D11DeviceContext* context);

	Mesh mesh;

	//setters
	//getters

private:

	
	//materials?
	//shaders

};