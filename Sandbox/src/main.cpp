
#include "../../Runtime/src/SceneManager.h"
#include "../../Runtime/src/Window.h"

using namespace rl;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	std::wstring test = L"name";
	Window window(hInst, nullptr, test, WS_OVERLAPPEDWINDOW, 1280, 720, true);

	//SceneManager::Scene* scene = SceneManager::CreateScene();

	/*Entity* player = scene->CreateEntity();
	player->transform.setPosition(0, 2, -10);
	Camera* camera = Graphics::createCamera(player);
	Camera::setMainCamera(camera);
	camera->fov = 60;

	Entity* object = scene->CreateEntity();
	MeshRenderer* mesh = Graphics::createMesh(object);
	//mesh->getMesh()->ImportObj("assets/untitled.obj");

	Entity* sun = scene->CreateEntity();
	sun->transform.setRotation(45, 45, 0);
	DirectionalLight* light = Graphics::createDirectionalLight(sun);*/


	//Input::setCursorState(CursorState::Hidden);

	Window::ExitCode exitCode = window.Run();
	while(!exitCode.close)
	{
		/*float speed = Time::deltaTime() * 5;
		if (Input::getKey('W'))
			player->transform.Translate(0, 0, speed);
		if (Input::getKey('A'))
			player->transform.Translate(-speed, 0, 0);
		if (Input::getKey('S'))
			player->transform.Translate(0, 0, -speed);
		if (Input::getKey('D'))
			player->transform.Translate(speed, 0, 0);
		if (Input::getKey('Q'))
			player->transform.Translate(0, -speed, 0);
		if (Input::getKey('E'))
			player->transform.Translate(0, speed, 0);
		if (Input::getKey(0x1B))
			break;

		float sensitivity = 50 * Time::deltaTime();
		Vec2 mouse = Input::getMouse();
		player->transform.Rotate(mouse.y * sensitivity, mouse.x * sensitivity, 0);*/

		exitCode = window.Run();
	}

	return exitCode.exitCode;
}