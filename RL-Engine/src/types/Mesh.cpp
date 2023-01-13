#include "../../include/types/Mesh.h"

using namespace msclr::interop;

Engine::Mesh::Mesh(Core::Mesh* mesh) : Managed(mesh) {

}

void Engine::Mesh::ImportObj(System::String^ fileName) {
	instance->ImportObj(marshal_as<std::string>(fileName));
}