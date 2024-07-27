#pragma once

#include <memory>
#include <queue>
#include <vector>
#include <filesystem>

#include <types/Types.h>

#include "../GuiElement.h"
#include "ecs/ComponentType.h"

namespace rl::ed
{
    class SceneHierarchy : public GuiElement
    {
    public:
        ~SceneHierarchy() override = default;

        static void OpenWindow();
        static void CloseWindow();

        void Render() override;
        bool IsOpen() override;

        static void SetEntityName(rl::Entity entity, const std::string& name);
        static void SetFolderName(size_t folder, const std::string& name);

        static void NewScene(const std::filesystem::path& file);
        static void OpenScene(const std::filesystem::path& file);
        static void SaveScene();

    private:
        enum class ElementType : u8
        {
            Entity = 0,
            Folder = 1,
            FolderEnd = 2
        };

        struct Element
        {
            ElementType type;
            size_t id = 0;
            std::string name;
            bool enabled = true;

            Element() = delete;
            Element(ElementType type, size_t id, std::string name) : type(type), id(id), name(std::move(name)) {}
        };

        std::vector<Element> hierarchy = std::vector<Element>();
        std::deque<size_t> deletedFolders = std::deque<size_t>();
        size_t nextFolder = 0;

        std::string moving;
        bool moved = false;
        bool rightClickedEnabled = false;
        size_t rightClickedElement = 0;

        static std::shared_ptr<SceneHierarchy> window;
        bool open = true;

        std::filesystem::path filePath = "/";

        void DrawHierarchy();
        [[nodiscard]] int GetHierarchyElementSize(int element) const;
        [[nodiscard]] bool TryMoveElement(int elementIndex);
        [[nodiscard]] bool DrawRightClickMenu(ElementType type, int index);
    };
}
