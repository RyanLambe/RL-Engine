#include "../../include/objects/MeshRenderer.h"

Core::MeshRenderer::MeshRenderer(Entity* parent) : Component(parent) {
	
	setType("MeshRenderer");
	mesh.ImportObj("assets/storus.obj");
}

Core::MeshRenderer::MeshRenderer(const MeshRenderer& other) : Component(other.entity) {
	setType("MeshRenderer");
	this->material = other.material;
	this->mesh = other.mesh;
}

void Core::MeshRenderer::Draw(SmartPtr<ID3D11Device> device, SmartPtr<ID3D11DeviceContext> context) {

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

void Core::MeshRenderer::setMaterial(Material mat)
{
	this->material = mat;
}

void Core::MeshRenderer::setMesh(Mesh mesh)
{
	this->mesh = mesh;
}

Core::Material* Core::MeshRenderer::getMaterial() {
	return &material;
}

Core::Mesh* Core::MeshRenderer::getMesh()
{
	return &mesh;
}
