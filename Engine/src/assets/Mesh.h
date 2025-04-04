#pragma once

#include "../types/Types.h"
#include "../types/Vertex.h"
#include "Asset.h"

namespace rl
{
    class MeshData : public AssetData
    {
    public:
        MeshData() = default;

        [[nodiscard]] const std::vector<uint32_t>& GetIndices() const;
        [[nodiscard]] const std::vector<Vertex>& GetVertices() const;
        [[nodiscard]] size_t GetIndexCount() const;

    private:
        void ImportFile(const std::filesystem::path& file) override;
        void ReadFile(std::ifstream& input) override;
        void WriteData(std::ofstream& output) override;

        std::vector<Vertex> vertices;
        std::vector<u32> indices;
    };
}
