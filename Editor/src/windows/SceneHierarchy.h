#pragma once

#include <memory>
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

    private:
        static std::shared_ptr<SceneHierarchy> window;
        bool open = true;

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
        Entity nextEntity = 0;
        size_t nextFolder = 0;
        std::string moving;

        [[nodiscard]] int GetHierarchyElementSize(int element) const;
    };
}
