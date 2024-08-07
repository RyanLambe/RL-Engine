#pragma once

#include <memory>
#include <queue>
#include <vector>

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

    private:
        enum class ElementType : uint8_t
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
        std::queue<size_t> deletedFolders = std::queue<size_t>();
        size_t nextFolder = 0;

        std::string moving;
        bool moved = false;
        bool rightClickedEnabled = false;
        size_t rightClickedElement = 0;

        static std::shared_ptr<SceneHierarchy> window;
        bool open = true;

        void DrawHierarchy();
        [[nodiscard]] int GetHierarchyElementSize(int element) const;
        [[nodiscard]] bool TryMoveElement(int elementIndex);
        [[nodiscard]] bool DrawRightClickMenu(ElementType type, int index);
    };
}
