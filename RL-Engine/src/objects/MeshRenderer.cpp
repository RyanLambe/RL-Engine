#include "../../include/objects/MeshRenderer.h"

MeshRenderer::MeshRenderer(ID3D11Device* device, ID3D11DeviceContext* context, Entity* parent) : Component(parent), shader(device, context) {
	
	mesh.ImportObj("assets/storus.obj");
	mesh.Update(device, context);
}

void MeshRenderer::Draw(ID3D11Device* device, ID3D11DeviceContext* context) {
	
	//update material
	material.Update(device, context);

	//send transformation matrix to vertex shader
	entity->getTransform()->UpdateBuffer(device, context);

	//draw
	context->DrawIndexed(mesh.getIndices().size(), 0, 0);
}

Material* MeshRenderer::getMaterial() {
	return &material;
}
