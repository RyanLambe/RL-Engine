#include "../../include/types/Mesh.h"

void Mesh::Update(ID3D11Device* device, ID3D11DeviceContext* context) {

	//create buffers
	CreateBuffer(vertices.data(), sizeof(Vertex) * vertices.size(), D3D11_BIND_VERTEX_BUFFER, &vertexBuffer, device);
	CreateBuffer(indices.data(), sizeof(unsigned int) * indices.size(), D3D11_BIND_INDEX_BUFFER, &indexBuffer, device);

	// set buffers
	UINT offset = 0;
	UINT stride = sizeof(Vertex);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Mesh::setVertices(std::vector<Vertex> vertices) {
	this->vertices = vertices;
}

std::vector<Mesh::Vertex> Mesh::getVertices() {
	return vertices;
}

void Mesh::setIndices(std::vector<unsigned int> indices) {
	this->indices = indices;
}

std::vector<unsigned int> Mesh::getIndices() {
	return indices;
}

void Mesh::CreateBuffer(void* data, UINT size, UINT bindFlags, ID3D11Buffer** buffer, ID3D11Device* device) {

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = bindFlags;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	device->CreateBuffer(&bufferDesc, &initData, buffer);
}