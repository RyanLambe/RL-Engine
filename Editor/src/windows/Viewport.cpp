#include "Viewport.h"
#include <imgui.h>
#include <graphics/Renderer.h>

#include "components/Camera.h"
#include "../Editor.h"

using namespace rl::editor;

Viewport::Viewport() {
    target = RenderTarget::Create(1, 1, Application::GetRenderer().GetContext());
}

void Viewport::Render() {

    if(ImGui::Begin("Renderer", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse)){

        if(Camera::GetMain() == nullptr){
            ImGui::End();
            return;
        }

        target->Resize((int)ImGui::GetContentRegionAvail().x, (int)ImGui::GetContentRegionAvail().y);
        ImGui::Image( target->GetTexture(), ImGui::GetContentRegionAvail());
        ImGui::End();
        target->Clear();
    }
    else{
        open = false;
        return;
    }

    target->Enable();
    Application::GetRenderer().Render();
    Application::GetRenderer().EnableTarget();
}

bool Viewport::IsOpen() {
    return open;
}
