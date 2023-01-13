#include "../include/Input.h"

//keyboard
bool Engine::Input::getKey(UINT key) {
	return Core::Input::getKey(key);
}

//mouse
Engine::Vec2^ Engine::Input::getMousePos() {
	return gcnew Vec2(&Core::Input::getMousePos());
}
Engine::Vec2^ Engine::Input::getMouse() {
	return gcnew Vec2(&Core::Input::getMouse());
}
bool Engine::Input::getMouseButton(int button) {
	return Core::Input::getMouseButton(button);
}
float Engine::Input::getMouseWheel() {
	return Core::Input::getMouseWheel();
}

//cursor
void Engine::Input::setCursorState(int state) {
	
	Core::Input::setCursorState((Core::CursorState)state);
}