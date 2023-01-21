#include "../../include/objects/MeshRenderer.h"

using namespace Engine;
using namespace msclr::interop;

MeshRenderer::MeshRenderer() :
	Entity::Component(Core::Graphics::createMesh(nullptr)) {

}

MeshRenderer::MeshRenderer(Entity^ entity) :
	Entity::Component(Core::Graphics::createMesh(entity->GetInstance()))
{

}

MeshRenderer::MeshRenderer(Core::MeshRenderer* mesh) : 
	Entity::Component(mesh) {

}

MeshRenderer^ MeshRenderer::CastAs(Entity::Component^ component) {
	if (component == nullptr)
		return nullptr;
	if (component->GetInstance())
		return gcnew MeshRenderer((Core::MeshRenderer*)component->GetInstance());
	return nullptr;
}

void MeshRenderer::setMaterial(Material^ mat) {
	GetInstance<Core::MeshRenderer>()->getMaterial()->settings.color.r = mat->color.r;
	GetInstance<Core::MeshRenderer>()->getMaterial()->settings.color.g = mat->color.g;
	GetInstance<Core::MeshRenderer>()->getMaterial()->settings.color.b = mat->color.b;
	GetInstance<Core::MeshRenderer>()->getMaterial()->settings.color.a = mat->color.a;

	GetInstance<Core::MeshRenderer>()->getMaterial()->settings.smoothness = mat->smoothness;
	GetInstance<Core::MeshRenderer>()->getMaterial()->settings.reflectivity = mat->reflectivity;

	GetInstance<Core::MeshRenderer>()->getMaterial()->settings.glow = mat->glow;

	System::String^ test = mat->textureName;
	GetInstance<Core::MeshRenderer>()->getMaterial()->SetTexture(marshal_as<std::string>(test));
}

void MeshRenderer::setMesh(Mesh^ mesh) {
	//move mesh data to core mesh
	GetInstance<Core::MeshRenderer>()->getMesh()->Refresh();
}

void MeshRenderer::ImportMeshObj(System::String^ fileName) {
	GetInstance<Core::MeshRenderer>()->getMesh()->ImportObj(marshal_as<std::string>(fileName));
}

Material^ MeshRenderer::getMaterial() {
	Material^ mat = gcnew Material();

	mat->color.r = GetInstance<Core::MeshRenderer>()->getMaterial()->settings.color.r;
	mat->color.g = GetInstance<Core::MeshRenderer>()->getMaterial()->settings.color.g;
	mat->color.b = GetInstance<Core::MeshRenderer>()->getMaterial()->settings.color.b;
	mat->color.a = GetInstance<Core::MeshRenderer>()->getMaterial()->settings.color.a;

	mat->smoothness = GetInstance<Core::MeshRenderer>()->getMaterial()->settings.smoothness;
	mat->reflectivity = GetInstance<Core::MeshRenderer>()->getMaterial()->settings.reflectivity;

	mat->glow = GetInstance<Core::MeshRenderer>()->getMaterial()->settings.glow;

	mat->textureName = marshal_as<System::String^>(GetInstance<Core::MeshRenderer>()->getMaterial()->settings.textureName);

	return mat;
}

Mesh^ MeshRenderer::getMesh() {
	Mesh^ mesh = gcnew Mesh();

	//move core mesh data to mesh output

	return mesh;
}