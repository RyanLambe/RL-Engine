#include "Viewport.h"

#include <imgui.h>

#include "../Editor.h"
#include "components/Camera.h"

using namespace rl::editor;

void Viewport::Render()
{
    if (ImGui::Begin("Renderer", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
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
    else
    {
        open = false;
        return;
    }
}

bool Viewport::IsOpen()
{
    return open;
}
