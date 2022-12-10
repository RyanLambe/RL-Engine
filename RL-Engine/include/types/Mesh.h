#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <vector>

class Mesh {
public:
	struct Vertex {
		float x;
		float y;
		float z;
	};

public:

	//constructor???
	void setVertices(std::vector<Vertex> vertices);
	std::vector<Vertex> getVertices();
	void setIndices(std::vector<unsigned int> indices);
	std::vector<unsigned int> getIndices();

	void Update(ID3D11Device* device, ID3D11DeviceContext* context);

	void CreateBuffer(void* data, UINT size, UINT bindFlags, ID3D11Buffer** buffer, ID3D11Device* device);

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices; 

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
};