#include "../../pch.h"
#include "../../include/types/Mesh.h"

using namespace msclr::interop;

Engine::Mesh::Mesh() : Managed(new Core::Mesh()) {

}

void Engine::Mesh::ImportObj(System::String^ fileName) {
	instance->ImportObj(marshal_as<std::string>(fileName));
}