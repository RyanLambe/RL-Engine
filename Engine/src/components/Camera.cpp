#include "Camera.h"

rl::Camera* rl::Camera::main = nullptr;


rl::Camera* rl::Camera::GetMain()
{
	return main;
}

void rl::Camera::SetMain(Camera* cam)
{
	main = cam;
}

void rl::Camera::SetMain()
{
	main = this;
}
