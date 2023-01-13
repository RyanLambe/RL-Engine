#include "../../include/objects/MeshRenderer.h"

Core::MeshRenderer::MeshRenderer(Entity* parent) : Component(parent) {
	
	mesh.ImportObj("assets/storus.obj");
}

void Core::MeshRenderer::Draw(ID3D11Device* device, ID3D11DeviceContext* context) {

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
