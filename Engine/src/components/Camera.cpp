#include "Camera.h"

#include "../core/Application.h"

rl::Camera* rl::Camera::GetMain()
{
    return Application::GetScene().mainCamera;
}

void rl::Camera::SetMain(Camera* cam)
{
    Application::GetScene().mainCamera = cam;
}

void rl::Camera::SetMain()
{
    Application::GetScene().mainCamera = this;
}

bool rl::Camera::IsMain() const
{
    return GetEntity() == Application::GetScene().mainCamera->GetEntity();
}

void rl::Camera::RenderToWindow()
{
    renderTarget = RenderTarget::Create(Application::GetWindowPtr(), Application::GetGraphicsContextPtr());
    width = Application::GetWindow().GetWidth();
    height = Application::GetWindow().GetHeight();
}

void rl::Camera::RenderToTarget(uint32_t targetWidth, uint32_t targetHeight)
{
    renderTarget = RenderTarget::Create(targetWidth, targetHeight, Application::GetGraphicsContextPtr());
    width = targetWidth;
    height = targetHeight;
}

void rl::Camera::ResizeTarget(uint32_t targetWidth, uint32_t targetHeight)
{
    if (targetWidth <= 0 || targetHeight <= 0)
        return;
    if (targetWidth == width && targetHeight == height)
        return;
    width = targetWidth;
    height = targetHeight;
    renderTarget->Resize(targetWidth, targetHeight);
}

void rl::Camera::EnableTarget()
{
    renderTarget->Enable();
}
