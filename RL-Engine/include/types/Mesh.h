#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Vec3.h"
#include "Vec2.h"

class Mesh {
public:

	struct Vertex {
		struct position {
			float x;
			float y;
			float z;
		} position;

		struct texCoords {
			float u;
			float v;
		} texCoords;

		struct normal {
			float x;
			float y;
			float z;
		} normal;

		bool operator==(const Vertex& other) const {
			if (position.x != other.position.x)
				return false;
			if (position.y != other.position.y)
				return false;
			if (position.z != other.position.z)
				return false;

			if (texCoords.u != other.texCoords.u)
				return false;
			if (texCoords.v != other.texCoords.v)
				return false;

			if (normal.x != other.normal.x)
				return false;
			if (normal.y != other.normal.y)
				return false;
			if (normal.z != other.normal.z)
				return false;

			return true;
		}
	};

public:

	Mesh();

	void setVertices(std::vector<Vertex> vertices);
	std::vector<Vertex> getVertices();
	void setIndices(std::vector<unsigned int> indices);
	std::vector<unsigned int> getIndices();

	void Update(ID3D11Device* device, ID3D11DeviceContext* context);

	void Refresh();

	void ImportObj(std::string fileName);

private:

	void CreateBuffer(void* data, UINT size, UINT bindFlags, ID3D11Buffer** buffer, ID3D11Device* device);
	
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices; 

	bool refresh = true;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
};