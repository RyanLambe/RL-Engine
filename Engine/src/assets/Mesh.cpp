#include "Mesh.h"

#include <fstream>

#include "../core/Logger.h"

namespace rl
{
    void Mesh::ImportFile(const std::filesystem::path& file)
    {
        std::ifstream fileStream(file);
        if (!fileStream.is_open())
        {
            RL_LOG_ERROR("Cannot open mesh file.");
            return;
        }

        std::string line;

        std::vector<glm::vec3> verts;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> norms;

        while (getline(fileStream, line))
        {
            // faces
            if (line.at(0) == 'f')
            {
                // f a1/a2/a3 b1/b2/b3 c1/c2/c3
                // remove slashes and replace with spaces, so it is readable by iss
                for (int i = 0; i < line.length(); i++)
                {
                    if (line.at(i) == '/')
                        line.at(i) = ' ';
                }

                std::istringstream iss(line.substr(1, line.length()));

                // get all ints from string
                int curVert[3];
                int curUV[3];
                int curNorm[3];
                iss >> curVert[0] >> curUV[0] >> curNorm[0] >> curVert[1] >> curUV[1] >> curNorm[1] >> curVert[2]
                    >> curUV[2] >> curNorm[2];

                // move vertex data into vertex struct
                for (int i = 0; i < 3; i++)
                {
                    Vertex temp {};
                    temp.position.x = verts[curVert[i] - 1].x;
                    temp.position.y = verts[curVert[i] - 1].y;
                    temp.position.z = verts[curVert[i] - 1].z;

                    temp.texCoords.x = uvs[curUV[i] - 1].x;
                    temp.texCoords.y = 1 - uvs[curUV[i] - 1].y;

                    temp.normal.x = norms[curNorm[i] - 1].x;
                    temp.normal.y = norms[curNorm[i] - 1].y;
                    temp.normal.z = norms[curNorm[i] - 1].z;

                    // check if vertex exists
                    bool exists = false;
                    for (int j = 0; j < vertices.size(); j++)
                    {
                        if (vertices[j] == temp)
                        {
                            indices.push_back(j);
                            exists = true;
                        }
                    }

                    if (!exists)
                    {
                        vertices.push_back(temp);
                        indices.push_back(vertices.size() - 1);
                    }
                }

                continue;
            }

            if (line.at(0) != 'v')
                continue;

            std::istringstream iss(line.substr(2, line.length()));
            float x = 0, y = 0, z = 0;

            // uv coords
            if (line.at(1) == 't')
            {
                iss >> x >> y;
                uvs.emplace_back(x, y);
                continue;
            }

            iss >> x >> y >> z;

            // normals
            if (line.at(1) == 'n')
            {
                norms.emplace_back(x, y, z);
                continue;
            }

            // vertex
            verts.emplace_back(x, y, z);
        }
    }

    void Mesh::ReadFile(std::ifstream &input) {

    }

    void Mesh::WriteData(std::ofstream& output) {
        output << vertices.size() << indices.size();
        output.write((char*)&vertices[0], vertices.size() * sizeof(Vertex));
        output.write((char*)&indices[0], indices.size() * sizeof(uint32_t));
    }

    const std::vector<Vertex>& Mesh::GetVertices() const
    {
        return vertices;
    }

    const std::vector<uint32_t>& Mesh::GetIndices() const
    {
        return indices;
    }

    size_t Mesh::GetIndexCount() const
    {
        return indices.size();
    }
}