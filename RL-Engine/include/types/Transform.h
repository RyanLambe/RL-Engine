#pragma once
#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "../types/Vec3.h"

namespace Engine {
	public ref class Transform/* : public Managed<Core::Transform> */{
	public:
		//engine use
		Transform(Core::Transform* transform);
		Core::Transform* getCoreFormat();

		//directions
		Vec3^ foreward();
		Vec3^ right();
		Vec3^ up();

		//position
		void setPosition(Vec3^ position);
		void setPosition(float x, float y, float z);
		void Translate(Vec3^ offset);
		void Translate(float x, float y, float z);
		Vec3^ getPosition();

		//rotation
		void setRotation(Vec3^ rotation);
		void setRotation(float x, float y, float z);
		void Rotate(Vec3^ offset);
		void Rotate(float x, float y, float z);
		Vec3^ getRotation();

		//scale
		void setScale(Vec3^ scale);
		void setScale(float x, float y, float z);
		void setScale(float scale);
		void Scale(Vec3^ scale);
		void Scale(float x, float y, float z);
		void Scale(float scale);
		Vec3^ getScale();

	private:
		Core::Transform* instance;
	};
}