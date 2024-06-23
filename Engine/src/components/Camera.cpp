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
