#include "MeshComponent.h"
#include <fstream>

void rl::MeshComponent::Enable() const {
    vertexBuffer->Enable();
    indexBuffer->Enable();
}

uint32_t rl::MeshComponent::GetIndexCount() const {
    return indexCount;
}

void rl::MeshComponent::LoadMesh(const std::string& fileName, Renderer* renderer) {
    std::ifstream file(fileName);
    std::string line;

    std::vector<glm::vec3> verts;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> norms;

    std::vector<Vertex> out;
    std::vector<unsigned int> inds;

    while (getline(file, line)) {

        //faces
        if (line.at(0) == 'f') {

            //f a1/a2/a3 b1/b2/b3 c1/c2/c3
            //remove slashes and replace with spaces, so it is readable by iss
            for (int i = 0; i < line.length(); i++) {
                if (line.at(i) == '/')
                    line.at(i) = ' ';
            }

            std::istringstream iss(line.substr(1, line.length()));

            //get all ints from string
            int curVert[3];
            int curUV[3];
            int curNorm[3];
            iss >> curVert[0] >> curUV[0] >> curNorm[0] >> curVert[1] >> curUV[1] >> curNorm[1] >> curVert[2]
                >> curUV[2] >> curNorm[2];

            //move vertex data into vertex struct
            for (int i = 0; i < 3; i++) {

                Vertex temp{};
                temp.position.x = verts[curVert[i] - 1].x;
                temp.position.y = verts[curVert[i] - 1].y;
                temp.position.z = verts[curVert[i] - 1].z;

                temp.texCoords.x = uvs[curUV[i] - 1].x;
                temp.texCoords.y = 1 - uvs[curUV[i] - 1].y;

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

    // save data
    vertexBuffer = VertexBuffer::Create(out, false, renderer->GetContext());
    indexBuffer = IndexBuffer::Create(inds, false, renderer->GetContext());
    indexCount = (uint32_t)inds.size();
}