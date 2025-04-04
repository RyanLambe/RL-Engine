#pragma once

#include <filesystem>
#include <memory>

#include "../GuiElement.h"

namespace rl::ed
{
    class AssetManager : public GuiElement
    {
    public:
        ~AssetManager() override = default;
        AssetManager() = default;

        static void OpenNewAssetPopup(const std::filesystem::path& location);
        static void OpenImportAssetPopup(const std::filesystem::path& file);
        static void ClosePopup();

        void Render() override;
        bool IsOpen() override;

    private:
        static std::shared_ptr<AssetManager> popup;
        bool open = true;

        bool importAsset = false;
        std::filesystem::path location;
        char filenameBuf[256] = {0};


    };
}
