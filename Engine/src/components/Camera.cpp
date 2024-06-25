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

bool rl::Camera::IsMain() const {
    return GetEntity() == Application::GetScene().mainCamera->GetEntity();
}

void rl::Camera::RenderToWindow()
{
    renderTarget = RenderTarget::Create(Application::GetWindowPtr(), Application::GetGraphicsContextPtr());
    width = Application::GetWindow().getWidth();
    height = Application::GetWindow().getHeight();
}

void rl::Camera::RenderToTarget(uint32_t width, uint32_t height)
{
    renderTarget = RenderTarget::Create(width, height, Application::GetGraphicsContextPtr());
    this->width = width;
    this->height = height;
}

void rl::Camera::ResizeTarget(uint32_t width, uint32_t height) {
    if(width <= 0 || height <= 0)
        return;
    if(width == this->width && height == this->height)
        return;
    this->width = width;
    this->height = height;
    renderTarget->Resize(width, height);
}

void rl::Camera::EnableTarget() {
    renderTarget->Enable();
}
