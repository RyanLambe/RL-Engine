#pragma once

#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <wrl.h>

#include "Debug.h"
#include "objects/MeshRenderer.h"
#include "objects/PointLight.h"
#include "objects/DirectionalLight.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#define MaxTotalLights 128
#define MaxLights 8

namespace Core {
	class Graphics
	{
	public:
		Graphics();
		Graphics(const Graphics&) = delete;
		void Start(HWND hwnd, int width, int height);
		void EndFrame();
		void Draw();

		static MeshRenderer* createMesh(Entity* parent);
		static PointLight* createPointLight(Entity* parent);
		static DirectionalLight* createDirectionalLight(Entity* parent);
		static Camera* createCamera(Entity* parent);
		static void setDirectionalLight(DirectionalLight* light);

		//[0] = top, [1] = bottom
		//[2] = left, [3] = right
		//[4] = front, [5] = back
		void setSkybox(std::string sides[6]);
		void setAmbientStrength(float strength);
		void setBackgroundColour(float colour[4]);

		static int getWidth();
		static int getHeight();

		void updateDimensions(int width, int height);
		void setFullscreen(bool fullscreen);

	private:

		void updateLightData();
		void updatePixelShader();
		void updateVertexShader();

	private:

		static int width;
		static int height;

		int windowedWidth = 0;
		int windowedHeight = 0;

		HWND hwnd;

		//constant buffers
		//vertex shader
		bool vsBufferCreated = false;
		Microsoft::WRL::ComPtr<ID3D11Buffer> vsBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
		struct VSBufferData {
			DirectX::XMMATRIX camMatrix;
			DirectX::XMVECTOR lightPos[MaxTotalLights + 1];
		} vsBufferData;

		//pixel shader
		bool psBufferCreated = false;
		Microsoft::WRL::ComPtr<ID3D11Buffer> psBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>();
		struct PSBufferData {

			struct DirectionalLightDetails {
				float r;
				float g;
				float b;
				float space; // space to align floats by 4
			}dirLightDetails;

			struct PointLightDetails {
				float r;
				float g;
				float b;
				float power;
				float range;
				float space1, space2, space3; // spaces to align floats by 4
			}pntLightDetails[MaxLights];

			struct AmbientLight {
				float r;
				float g;
				float b;
				float space; // space to align floats by 4
			}ambientLight;

		} psBufferData;

		//meshs to be rendered
		static std::vector<Camera> cameras;
		static std::vector<MeshRenderer> renderers;
		Shader shader;

		//lights
		float ambientStrength = 0.5f;
		bool skyboxEnabled = false;
		float backgroundColour[4] = { 1, 155.0f / 255.0f, 0, 1 };

		static std::vector<PointLight> pointLights;
		static std::vector<DirectionalLight> dirLights;
		static DirectionalLight* directionalLight;

		//skybox
		Entity skybox;

		//rendering
		static Microsoft::WRL::ComPtr<IDXGISwapChain> swap;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>();
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV = Microsoft::WRL::ComPtr<ID3D11DepthStencilView>();

		//accessing directX
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
		static Microsoft::WRL::ComPtr<ID3D11Device> device;

		//textures
		Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler = Microsoft::WRL::ComPtr<ID3D11SamplerState>();
	};
}
