#pragma once

#include <directxmath.h>
#include <d3d11.h>
#include <wrl.h>

#include <glm/glm.hpp>

#include "Vec3.h"

namespace rl {

	class Entity;

	class Transform {
	public:
		//engine use
		~Transform();
		Transform();
		Transform(Entity* entity);
		Transform(const Transform&) = delete;
		Transform& operator=(const Transform&) = delete;

		void UpdateBuffer(ID3D11Device* device, ID3D11DeviceContext* context);
		//DirectX::XMMATRIX getMatrix();
        glm::mat4 getMatrix();

		//directions
		Vec3 foreward();
		Vec3 right();
		Vec3 up();

		//transformation functions
		void setPosition(Vec3 position);
		void setPosition(float x, float y, float z);
		void Translate(Vec3 offset);
		void Translate(float x, float y, float z);
		Vec3 getPosition();

		void setRotation(Vec3 rotation);
		void setRotation(float x, float y, float z);
		void Rotate(Vec3 offset);
		void Rotate(float x, float y, float z);
		Vec3 getRotation();

		void setScale(Vec3 scale);
		void setScale(float x, float y, float z);
		void setScale(float scale);
		void Scale(Vec3 scale);
		void Scale(float x, float y, float z);
		void Scale(float scale);
		Vec3 getScale();

	private:
		//constant buffer data
		glm::mat4 matrix;
        //DirectX::XMMATRIX matrix;
		Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
		bool bufferCreated = false;

		//transform data
		Entity* entity = nullptr;
		Vec3 position = Vec3();
		Vec3 rotation = Vec3();
		Vec3 scale = Vec3(1);
	};
}