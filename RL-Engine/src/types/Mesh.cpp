#include "../../include/types/Mesh.h"

void Mesh::Update() {

	//create vertex buffer
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = vertices.getArray();
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	Graphics::device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);

	//create index buffer
	bufferDesc.ByteWidth = sizeof(indices);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	initData.pSysMem = indices.getArray();

	Graphics::device->CreateBuffer(&bufferDesc, &initData, &indexBuffer);


	//set buffers
	UINT offset = 0;
	UINT stride = sizeof(Vertex);
	Graphics::context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	Graphics::context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Mesh::setVertices(LinkedList<Vertex> vertices) {
	this->vertices = vertices;
}

LinkedList<Mesh::Vertex> Mesh::getVertices() {
	return vertices;
}

void Mesh::setIndices(LinkedList<unsigned int> indices) {
	this->indices = indices;
}

LinkedList<unsigned int> Mesh::getIndices() {
	return indices;
}