#include "../../include/objects/MeshRenderer.h"

MeshRenderer::MeshRenderer() {
	
	//set indices
	unsigned int indis[] = {
		0, 2, 1,  2, 3, 1,
		1, 3, 5,  3, 7, 5,
		2, 6, 3,  3, 6, 7,
		4, 5, 7,  4, 7, 6,
		0, 4, 2,  2, 4, 6,
		0, 1, 4,  1, 5, 4
	};
	LinkedList<unsigned int> indices;
	for (int i = 0; i < 36; i++)
		indices.put(indis[i]);
	
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
	LinkedList<Mesh::Vertex> vertices;
	for (int i = 0; i < 8; i++)
		vertices.put(verts[i]);

	mesh.setVertices(vertices);

	mesh.Update();
}

void MeshRenderer::Draw() {
	
	//do stuff?

	Graphics::context->DrawIndexed(mesh.getIndices().size(), 0, 0);
}