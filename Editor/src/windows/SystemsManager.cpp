#include "SystemsManager.h"

#include "../Editor.h"

namespace rl::ed {

    std::shared_ptr<SystemsManager> SystemsManager::window = nullptr;

    void SystemsManager::OpenWindow()
    {
        if (!window)
        {
            window = std::make_shared<SystemsManager>();
        }
        window->open = true;
        Editor::AddGuiElement(window);
    }

    void SystemsManager::CloseWindow()
    {
        window->open = false;
    }

    void SystemsManager::Render() {
        if (ImGui::Begin("Systems Manager", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
        {
            ImGui::Text("Systems Manager");
            ImGui::Button("Hi :)");

            ImGui::End();
        }
    }

    bool SystemsManager::IsOpen() {
        return open;
    }
}