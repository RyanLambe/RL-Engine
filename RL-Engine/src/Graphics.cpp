#include "../include/Graphics.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

//update
void Graphics::Start(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	
	GfxThrowFailed(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swap, &device, nullptr, &context));

	// get render target
	Microsoft::WRL::ComPtr<ID3D11Texture2D> frameBuffer;
	swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&frameBuffer);
	device->CreateRenderTargetView(frameBuffer.Get(), 0, &target);
	
	// render closer object on top
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthState;
	device->CreateDepthStencilState(&dsDesc, &depthState);
	context->OMSetDepthStencilState(depthState.Get(), 1);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;
	D3D11_TEXTURE2D_DESC depthDesc = {};
	depthDesc.Width = 1280;
	depthDesc.Height = 720;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	device->CreateTexture2D(&depthDesc, nullptr, &depthTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc = {};
	DSVdesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVdesc.Texture2D.MipSlice = 0;
	device->CreateDepthStencilView(depthTexture.Get(), &DSVdesc, &DSV);

	context->OMSetRenderTargets(1, target.GetAddressOf(), DSV.Get());

	//set viewport size
	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);

	//set topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//setup sampler
	D3D11_SAMPLER_DESC sampleDesc = {};
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	device->CreateSamplerState(&sampleDesc, &sampler);
	context->PSSetSamplers(0, 1, sampler.GetAddressOf());

	lightData = { 0 };
}

//Draw Calls
void Graphics::EndFrame()
{
	HRESULT hr;
	if (FAILED(hr = swap->Present(0, 0))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			throw GfxExcept(Graphics::device->GetDeviceRemovedReason());
		else
			GfxThrowFailed(hr);
	}

	float background_colour[4] = { 255.0f/255.0f, 64.0f/255.0f, 0, 1.0f };
	context->ClearRenderTargetView(target.Get(), background_colour);
	context->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void Graphics::Draw() {

	//get view matrix
	DirectX::XMMATRIX viewMat = Camera::mainCamera->getViewMatrix();
	DirectX::XMMATRIX posMat = Camera::mainCamera->getPositionMatrix();

	updateCameraBuffer(posMat * viewMat);
	
	//handle lights
	updateLightBuffer();

	//render mesh renderers
	for (int i = 0; i < renderers.size(); i++) {
		renderers[i].Draw(device.Get(), context.Get());
	}
}

//Componenet Management
MeshRenderer* Graphics::createMesh(Entity* parent) {
	renderers.emplace_back(device.Get(), context.Get(), parent);
	parent->addComponent(&renderers[renderers.size() - 1]);
	return &renderers[renderers.size() - 1];
}

PointLight* Graphics::createPointLight(Entity* parent) {
	pointLights.emplace_back(parent);
	parent->addComponent(&pointLights[pointLights.size() - 1]);
	return &pointLights[pointLights.size() - 1];
}

void Graphics::setDirectionalLight(DirectionalLight* light) {
	directionalLight = light;
}


//Update Calls
void Graphics::updateLightData() {

	//get closest point lights
	PointLight* closest[MaxLights];

	//update positions
	Vec3 temp;

	if (directionalLight == nullptr) {
		lightData.positions[0] = DirectX::XMVectorSet(0, 0, 0, 0);
	}
	else {
		//get rotation of light and convert to rad
		temp = directionalLight->entity->getTransform()->getRotation();
		temp.x = temp.x * (pi / 180);
		temp.z = -temp.z * (pi / 180);
		temp.y = -temp.y * (pi / 180);
		
		//rotate -y unit vector around x and z axis
		Vec3 newDir;
		newDir.x = std::cos(temp.x) * -std::sin(temp.z);
		newDir.y = std::cos(temp.x) * std::cos(temp.z);
		newDir.z = std::sin(temp.x);
		
		//rotate new direction around y axis
		float x = newDir.x, z = newDir.z;
		newDir.x = (x * std::cos(temp.y)) - (z * std::sin(temp.y));
		newDir.z = (x * std::sin(temp.y)) + (z * std::cos(temp.y));


		lightData.positions[0] = DirectX::XMVectorSet(newDir.x, newDir.y, newDir.z, 1);
	}

	for (int i = 0; i < MaxLights; i++) {
		if (pointLights.size() <= i) {
			lightData.positions[i+1] = DirectX::XMVectorSet(0, 0, 0, 0);
			continue;
		}

		temp = pointLights[i].entity->getTransform()->getPosition();
		lightData.positions[i + 1] = DirectX::XMVectorSet(temp.x, temp.y, temp.z, 1);// {temp.x, temp.y, temp.z};
	}

	//update light properties
	if (directionalLight == nullptr)
		lightData.dirDetails = { 0, 0, 0 };
	else
		lightData.dirDetails = { directionalLight->Colour.x, directionalLight->Colour.y, directionalLight->Colour.z };

	for (int i = 0; i < MaxLights; i++) {
		if (pointLights.size() <= i) {
			lightData.pntDetails[i] = { 0, 0, 0 };
			continue;
		}

		temp = pointLights[i].Colour;
		lightData.pntDetails[i] = { temp.x, temp.y, temp.z };
		lightData.pntDetails[i].power = pointLights[i].power;
		lightData.pntDetails[i].range = pointLights[i].range;
	}
}

void Graphics::updateLightBuffer() {

	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;

	//update data before sending to buffer
	updateLightData();

	//update light positions
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(DirectX::XMVECTOR) * (MaxLights + 1);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &lightData.positions;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;
	
	//set constant buffer
	device->CreateBuffer(&bufferDesc, &initData, &constBuffer);
	context->VSSetConstantBuffers(2, 1, constBuffer.GetAddressOf());

	//make changes to settings
	bufferDesc.ByteWidth = sizeof(LightData::dirDetails) + sizeof(LightData::pntDetails) * MaxLights;
	initData.pSysMem = &lightData.dirDetails;

	//set new constant buffer
	device->CreateBuffer(&bufferDesc, &initData, &constBuffer);
	context->PSSetConstantBuffers(1, 1, constBuffer.GetAddressOf());
}

void Graphics::updateCameraBuffer(DirectX::XMMATRIX mat) {

	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuffer;

	//update 
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(mat);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &(mat);
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	//create constant buffer
	device->CreateBuffer(&bufferDesc, &initData, &constBuffer);
	context->VSSetConstantBuffers(1, 1, constBuffer.GetAddressOf());
}
