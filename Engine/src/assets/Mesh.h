#pragma once

#include "../types/Vertex.h"
#include "Asset.h"

namespace rl
{
    class Mesh : public Asset
    {
    public:
        Mesh() = default;

        [[nodiscard]] const std::vector<uint32_t>& GetIndices() const;
        [[nodiscard]] const std::vector<Vertex>& GetVertices() const;
        [[nodiscard]] size_t GetIndexCount() const;

    private:
        void ImportFile(const std::filesystem::path& file) override;
        void ReadFile(std::ifstream& input) override;
        void WriteData(std::ofstream& output) override;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
    };
}
