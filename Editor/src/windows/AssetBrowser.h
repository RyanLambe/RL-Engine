#pragma once

#include <memory>
#include <filesystem>

#include "../GuiElement.h"

namespace rl::ed {
    class AssetBrowser : public GuiElement {
    public:
        ~AssetBrowser() override = default;

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

        static void Setup(const std::string& projectDir);

    private:
        static std::shared_ptr<AssetBrowser> window;
        bool open = true;
        float iconSize = 125;

        std::filesystem::path rootPath;
        std::filesystem::path currPath;

        std::optional<std::filesystem::directory_entry> selectedFile = std::nullopt;
        bool newFileSelected = false;

        void DrawFileButton(const std::filesystem::directory_entry& entry);
        void DrawRightClickMenu() const;

        static std::string FixPathFormat(const std::string& path);
    };
}
