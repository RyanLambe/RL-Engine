#include "MeshRenderer.h"

using namespace rl;

MeshRenderer::MeshRenderer(Entity* parent) : Component(parent) {
	
	setType("MeshRenderer");
	mesh.ImportObj("assets/storus.obj");
}

MeshRenderer::MeshRenderer(const MeshRenderer& other) : Component(other.entity) {
	setType("MeshRenderer");
	this->material = other.material;
	this->mesh = other.mesh;
}

void MeshRenderer::Draw(ID3D11Device* device, ID3D11DeviceContext* context) {

	if (entity == nullptr)
		return;

	//update material
	material.Update(device, context);

	//update mesh
	mesh.Update(device, context);

	//send transformation matrix to vertex shader
	entity->transform.UpdateBuffer(device, context);

	//draw
	context->DrawIndexed(mesh.getIndices().size(), 0, 0);
}

void MeshRenderer::setMaterial(Material mat)
{
	this->material = mat;
}

void MeshRenderer::setMesh(const Mesh& mesh)
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
