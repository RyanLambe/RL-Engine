#include "Mesh.h"

using namespace rl;

Mesh::Mesh() {

}

void Mesh::Update(ID3D11Device* device, ID3D11DeviceContext* context) {

	if (refresh) {
		CreateBuffer(vertices.data(), sizeof(Vertex) * vertices.size(), D3D11_BIND_VERTEX_BUFFER, &vertexBuffer, device);
		CreateBuffer(indices.data(), sizeof(unsigned int) * indices.size(), D3D11_BIND_INDEX_BUFFER, &indexBuffer, device);
		refresh = false;
	}

	// set buffers
	UINT offset = 0;
	UINT stride = sizeof(Vertex);
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Mesh::Refresh()
{
	refresh = true;
}

void Mesh::ImportObj(std::string fileName) {

	std::ifstream file(fileName);
	std::string line;

	std::vector<Vec3> verts;
	std::vector<Vec2> uvs;
	std::vector<Vec3> norms;

	std::vector<Vertex> out;
	std::vector<unsigned int> inds;

	while (getline(file, line)) {

		//faces
		if (line.at(0) == 'f') {

			//f a1/a2/a3 b1/b2/b3 c1/c2/c3
			//remove slashs and replace with spaces so it is readable by iss
			for (int i = 0; i < line.length(); i++) {
				if (line.at(i) == '/')
					line.at(i) = ' ';
			}

			std::istringstream iss(line.substr(1, line.length()));

			//get all ints from string
			int curVert[3];
			int curUV[3];
			int curNorm[3];
			iss >> curVert[0] >> curUV[0] >> curNorm[0] >> curVert[1] >> curUV[1] >> curNorm[1] >> curVert[2] >> curUV[2] >> curNorm[2];

			//move vertex data into vertex struct
			for (int i = 0; i < 3; i++) {

				Vertex temp;
				temp.position.x = verts[curVert[i] - 1].x;
				temp.position.y = verts[curVert[i] - 1].y;
				temp.position.z = verts[curVert[i] - 1].z;

				temp.texCoords.u = uvs[curUV[i] - 1].x;
				temp.texCoords.v = 1 - uvs[curUV[i] - 1].y;

				if (norms[curNorm[i] - 1].x < 0) {
					int fst = 1;
					fst++;
				}

				temp.normal.x = norms[curNorm[i] - 1].x;
				temp.normal.y = norms[curNorm[i] - 1].y;
				temp.normal.z = norms[curNorm[i] - 1].z;

				//check if vertex exists
				bool exists = false;
				for (int j = 0; j < out.size(); j++) {
					if (out[j] == temp) {
						inds.push_back(j);
						exists = true;
					}
				}

				if (!exists) {
					out.push_back(temp);
					inds.push_back(out.size() - 1);
				}
			}

			continue;
		}
		
		if (line.at(0) != 'v')
			continue;

		
		std::istringstream iss(line.substr(2, line.length()));
		float x, y, z;

		//uv coords
		if (line.at(1) == 't') {
			iss >> x >> y;
			uvs.emplace_back(x, y);
			continue;
		}

		iss >> x >> y >> z;
			
		//normals
		if (line.at(1) == 'n') {
			norms.emplace_back(x, y, z);
			continue;
		}

		//vertex
		verts.emplace_back(x, y, z);
	}

	setVertices(out);
	setIndices(inds);

	Refresh();
}

Mesh& Mesh::operator=(const Mesh& other) {
	this->vertices = other.vertices;
	this->indices = other.indices;

	this->refresh = true;
	return *this;
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
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = bindFlags;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	Debug::logErrorCode(device->CreateBuffer(&bufferDesc, &initData, buffer));
}