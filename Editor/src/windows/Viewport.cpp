#include "Viewport.h"

#include <imgui.h>

#include "../Editor.h"
#include "components/Camera.h"

using namespace rl::ed;

void Viewport::Render()
{
    if (ImGui::Begin("Viewport", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
    {
        if (!Editor::Playing() || Camera::GetMain() == nullptr || Camera::GetMain()->GetRenderTarget() == nullptr)
        {
            ImGui::End();
            return;
        }

        Camera::GetMain()->ResizeTarget((int)ImGui::GetContentRegionAvail().x, (int)ImGui::GetContentRegionAvail().y);
        ImGui::Image(Camera::GetMain()->GetTexture(), ImGui::GetContentRegionAvail());
        ImGui::End();
    }
}

bool Viewport::IsOpen()
{
    return open;
}
