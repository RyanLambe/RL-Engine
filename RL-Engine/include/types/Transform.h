#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "../types/Vec3.h"

namespace Engine {
	public ref class Transform : public Managed<Core::Transform>{
	public:
		//engine use
		Transform();
		Transform(Core::Transform* transform);
		Transform(Core::Entity* entity);

		//directions
		Vec3^ foreward();
		Vec3^ right();
		Vec3^ up();

		//position
		void setPosition(Vec3^ position) { instance->setPosition(position->GetInstance()); }
		void setPosition(float x, float y, float z) { instance->setPosition(x, y, z); }
		void Translate(Vec3^ offset) { instance->Translate(offset->GetInstance()); }
		void Translate(float x, float y, float z) { instance->Translate(x, y, z); }
		Vec3^ getPosition() { return gcnew Vec3(instance->getPosition().x, instance->getPosition().y, instance->getPosition().z); }

		//rotation
		void setRotation(Vec3^ rotation) { instance->setRotation(rotation->GetInstance()); }
		void setRotation(float x, float y, float z) { instance->setRotation(x, y, z); }
		void Rotate(Vec3^ offset) { instance->Rotate(offset->GetInstance()); }
		void Rotate(float x, float y, float z) { instance->Rotate(x, y, z); }
		Vec3^ getRotation() { return gcnew Vec3(instance->getRotation().x, instance->getRotation().y, instance->getRotation().z); }

		//scale
		void setScale(Vec3^ scale) { instance->setScale(scale->GetInstance()); }
		void setScale(float x, float y, float z) { instance->setScale(x, y, z); }
		void setScale(float scale) { instance->setScale(scale, scale, scale); }
		void Scale(Vec3^ scale) { instance->Scale(scale->GetInstance()); }
		void Scale(float x, float y, float z) { instance->Scale(x, y, z); }
		void Scale(float scale) { instance->Scale(scale, scale, scale); }
		Vec3^ getScale() { return gcnew Vec3(instance->getScale().x, instance->getScale().y, instance->getScale().z); }

	};
}