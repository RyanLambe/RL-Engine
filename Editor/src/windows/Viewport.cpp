#include "Viewport.h"
#include <imgui.h>
#include <graphics/Renderer.h>

#include "components/Camera.h"

using namespace rl::editor;

void Viewport::Render() {

    if (Camera::GetMain() == nullptr)
        return;

    if(ImGui::Begin("Renderer", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse)){
        Renderer::Resize((int)ImGui::GetContentRegionAvail().x, (int)ImGui::GetContentRegionAvail().y);
        ImGui::Image( Renderer::GetRenderTexture(), ImGui::GetContentRegionAvail());
        ImGui::End();
    }
    else{
        open = false;
    }
}

bool Viewport::IsOpen() {
    return open;
}
