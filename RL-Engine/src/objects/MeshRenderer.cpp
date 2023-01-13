#include "../../include/objects/MeshRenderer.h"

using namespace Engine;
using namespace msclr::interop;

MeshRenderer::MeshRenderer(Entity^ entity) :
	ManagedComponent(Core::Graphics::createMesh(entity->GetInstance()), entity)
{

}

void MeshRenderer::setMaterial(Material^ mat) {
	instance->getMaterial()->settings.color.r = mat->color.r;
	instance->getMaterial()->settings.color.g = mat->color.g;
	instance->getMaterial()->settings.color.b = mat->color.b;
	instance->getMaterial()->settings.color.a = mat->color.a;

	instance->getMaterial()->settings.smoothness = mat->smoothness;
	instance->getMaterial()->settings.reflectivity = mat->reflectivity;

	instance->getMaterial()->settings.glow = mat->glow;

	System::String^ test = mat->textureName;
	instance->getMaterial()->SetTexture(marshal_as<std::string>(test));
}

void MeshRenderer::setMesh(Mesh^ mat) {

	instance->getMesh()->setIndices(mat->GetInstance()->getIndices());
	instance->getMesh()->setVertices(mat->GetInstance()->getVertices());
	instance->getMesh()->Refresh();
}

Material^ MeshRenderer::getMaterial() {
	Material^ mat = gcnew Material();

	mat->color.r = instance->getMaterial()->settings.color.r;
	mat->color.g = instance->getMaterial()->settings.color.g;
	mat->color.b = instance->getMaterial()->settings.color.b;
	mat->color.a = instance->getMaterial()->settings.color.a;

	mat->smoothness = instance->getMaterial()->settings.smoothness;
	mat->reflectivity = instance->getMaterial()->settings.reflectivity;

	mat->glow = instance->getMaterial()->settings.glow;

	mat->textureName = marshal_as<System::String^>(instance->getMaterial()->settings.textureName);

	return mat;
}

Mesh^ MeshRenderer::getMesh() {
	Mesh^ mesh = gcnew Mesh(instance->getMesh());

	mesh->GetInstance()->setIndices(instance->getMesh()->getIndices());
	mesh->GetInstance()->setVertices(instance->getMesh()->getVertices());

	return mesh;
}