#pragma once

#include <wrl.h>
#include "../Graphics.h"
#include "LinkedList.h"

class Mesh {
public:
	struct Vertex {
		float x;
		float y;
		float z;
	};

public:

	//constructor???

	void Update();

	void setVertices(LinkedList<Vertex> vertices);
	LinkedList<Vertex> getVertices();
	void setIndices(LinkedList<unsigned int> indices);
	LinkedList<unsigned int> getIndices();

private:
	LinkedList<Vertex> vertices;
	LinkedList<unsigned int> indices;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
};