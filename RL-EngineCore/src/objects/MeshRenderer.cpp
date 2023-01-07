#include "../../include/objects/MeshRenderer.h"

using namespace Core;

MeshRenderer::MeshRenderer(ID3D11Device* device, ID3D11DeviceContext* context, Entity* parent) : Component(parent), shader(device, context) {
	
	mesh.ImportObj("assets/storus.obj");
}

void MeshRenderer::Draw(ID3D11Device* device, ID3D11DeviceContext* context) {
	
	//update material
	material.Update(device, context);

	//update mesh
	mesh.Update(device, context);

	//send transformation matrix to vertex shader
	entity->transform.UpdateBuffer(device, context);

	//draw
	context->DrawIndexed(mesh.getIndices().size(), 0, 0);
}

void Core::MeshRenderer::setMaterial(Material mat)
{
	this->material = mat;
}

void Core::MeshRenderer::setMesh(Mesh mesh)
{
	this->mesh = mesh;
}

Material* MeshRenderer::getMaterial() {
	return &material;
}

Mesh* MeshRenderer::getMesh()
{
	return &mesh;
}
