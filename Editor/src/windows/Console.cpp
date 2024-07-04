#include "Console.h"

#include "../Editor.h"

namespace rl::editor
{
    std::shared_ptr<Console> Console::window = nullptr;

    void Console::OpenWindow()
    {
        if (!window)
        {
            window = std::make_shared<Console>();
        }
        window->open = true;
        Editor::AddGuiElement(window);
    }

    void Console::CloseWindow()
    {
        window->open = false;
    }

    void Console::Render()
    {
        if (ImGui::Begin("Console", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
        {
            ImGui::End();
        }
        else
        {
            open = false;
            return;
        }
    }

    bool Console::IsOpen()
    {
        return open;
    }
}