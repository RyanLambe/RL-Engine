#include "../../include/objects/MeshRenderer.h"

MeshRenderer::MeshRenderer(ID3D11Device* device, ID3D11DeviceContext* context, Entity* parent) : Component(parent), shader(device, context) {
	
	//set indices
	unsigned int indis[] = {
		0, 2, 1,  2, 3, 1,
		1, 3, 5,  3, 7, 5,
		2, 6, 3,  3, 6, 7,
		4, 5, 7,  4, 7, 6,
		0, 4, 2,  2, 4, 6,
		0, 1, 4,  1, 5, 4
	};
	std::vector<unsigned int> indices;
	for (int i = 0; i < 36; i++)
		indices.push_back(indis[i]);
	
	mesh.setIndices(indices);

	//set verts
	Mesh::Vertex verts[] = {
		{-1, -1, -1},
		{1, -1, -1},
		{-1, 1, -1},
		{1, 1, -1},
		{-1, -1, 1},
		{1, -1, 1},
		{-1, 1, 1},
		{1, 1, 1}
	}; 
	std::vector<Mesh::Vertex> vertices;
	for (int i = 0; i < 8; i++)
		vertices.push_back(verts[i]);

	mesh.setVertices(vertices);

	mesh.Update(device, context);
}

void MeshRenderer::Draw(ID3D11Device* device, ID3D11DeviceContext* context) {
	
	//update material
	material.Update(device, context);

	//get view matrix
	DirectX::XMMATRIX viewMat = Camera::mainCamera->getViewMatrix();

	//send transformation matrix to vertex shader
	entity->getTransform()->UpdateBuffer(device, context, viewMat);

	//draw
	context->DrawIndexed(mesh.getIndices().size(), 0, 0);
}

Material* MeshRenderer::getMaterial() {
	return &material;
}
