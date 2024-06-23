#include "Camera.h"

#include "../core/Application.h"

rl::Camera* rl::Camera::GetMain()
{
	return Application::GetMainCamera();
}

void rl::Camera::SetMain(Camera* cam)
{
    Application::SetMainCamera(cam);
}

void rl::Camera::SetMain()
{
    Application::SetMainCamera(this);
}
