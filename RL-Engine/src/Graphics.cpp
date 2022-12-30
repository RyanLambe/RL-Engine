#include "../include/Graphics.h"

#define checkError(code) if(FAILED(code)) throw std::exception(Debug::TranslateHResult(code).c_str())

int Graphics::width = 0;
int Graphics::height = 0;

//update
void Graphics::Start(HWND hwnd, int width, int height)
{

	//create device, context, and swap chain
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
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
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	
	checkError(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swap, &device, nullptr, &context));

	// get render target
	Microsoft::WRL::ComPtr<ID3D11Texture2D> frameBuffer;
	checkError(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&frameBuffer));
	checkError(device->CreateRenderTargetView(frameBuffer.Get(), 0, &target));

	// create depth stencil
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthState;
	checkError(device->CreateDepthStencilState(&dsDesc, &depthState));
	context->OMSetDepthStencilState(depthState.Get(), 1);

	//update size of window
	updateDimensions(width, height);

	//set topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//setup sampler
	D3D11_SAMPLER_DESC sampleDesc = {};
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	checkError(device->CreateSamplerState(&sampleDesc, &sampler));
	context->PSSetSamplers(0, 1, sampler.GetAddressOf());
}

//Draw Calls
void Graphics::EndFrame()
{
	HRESULT hr;
	if (FAILED(hr = swap->Present(0, 0))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			checkError(Graphics::device->GetDeviceRemovedReason());
		else
			Debug::logErrorCode(hr);
	}

	context->ClearRenderTargetView(target.Get(), backgroundColour);
	context->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void Graphics::Draw() {

	//get view matrix
	DirectX::XMMATRIX viewMat = Camera::mainCamera->getViewMatrix();
	DirectX::XMMATRIX posMat = Camera::mainCamera->getPositionMatrix();
	Vec3 camPos = Camera::mainCamera->entity->getTransform()->getPosition();

	//update buffers
	vsBufferData.camMatrix = posMat * viewMat;
	updateLightData();


	//updateCameraBuffer(posMat * viewMat);
	//updateLightBuffer();
	updateVertexShader();
	updatePixelShader();

	//update skybox
	skybox.getTransform()->setPosition(camPos);
	skybox.getTransform()->setRotation(0, 0, 0);
	skybox.getTransform()->setScale(Camera::mainCamera->farPlane/2, Camera::mainCamera->farPlane/2, Camera::mainCamera->farPlane/2);

	//render mesh renderers
	for (int i = 0; i < renderers.size(); i++) {
		renderers[i].Draw(device.Get(), context.Get());//check
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


void Graphics::setSkybox(std::string sides[6])
{
	//remove all components
	while (skybox.removeComponent<MeshRenderer>() != nullptr);

	float AverageColour[3] = { 0, 0, 0 };

	//add sides
	MeshRenderer* cur;
	for (int i = 0; i < 6; i++) {
		cur = createMesh(&skybox);
		std::string meshLoc = "assets/skybox/skybox-";
		meshLoc += std::to_string(i);
		meshLoc += ".obj";

		cur->getMesh()->ImportObj(meshLoc);
		cur->getMaterial()->settings.textureName = sides[i];
		cur->getMaterial()->settings.glow = 1;
		cur->getMaterial()->Update(device.Get(), context.Get());

		float* curAv = cur->getMaterial()->texture.getAverage();
		AverageColour[0] += curAv[0];
		AverageColour[1] += curAv[1];
		AverageColour[2] += curAv[2];
	}

	AverageColour[0] /= 6;
	AverageColour[1] /= 6;
	AverageColour[2] /= 6;

	backgroundColour[0] = AverageColour[0];
	backgroundColour[1] = AverageColour[1];
	backgroundColour[2] = AverageColour[2];
	backgroundColour[3] = 1;

	AverageColour[0] *= ambientStrength;
	AverageColour[1] *= ambientStrength;
	AverageColour[2] *= ambientStrength;

	psBufferData.ambientLight = { AverageColour[0], AverageColour[1], AverageColour[2], 1 };
	skyboxEnabled = true;
}

void Graphics::setAmbientStrength(float strength)
{
	ambientStrength = strength;
}

void Graphics::setBackgroundColour(float colour[4])
{
	//get rid of skybox
	while (skybox.removeComponent<MeshRenderer>() != nullptr);
	skyboxEnabled = false;

	for (int i = 0; i < 4; i++)
		backgroundColour[i] = colour[i];
}

int Graphics::getWidth()
{
	return width;
}

int Graphics::getHeight()
{
	return height;
}

void Graphics::updateDimensions(int width, int height)
{
	//save new dimensions
	this->width = width;
	this->height = height;

	DXGI_MODE_DESC dxgiDesc = {};
	dxgiDesc.Width = width;
	dxgiDesc.Height = height;
	dxgiDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	dxgiDesc.RefreshRate.Numerator = 0;
	dxgiDesc.RefreshRate.Denominator = 0;
	dxgiDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	dxgiDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Debug::logErrorCode(swap->ResizeTarget(&dxgiDesc));

	//update depth texture
	//create depth texture buffer
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture;
	D3D11_TEXTURE2D_DESC depthDesc = {};
	depthDesc.Width = width;
	depthDesc.Height = height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Debug::logErrorCode(device->CreateTexture2D(&depthDesc, nullptr, &depthTexture));

	//set depth texture so closer objects are on top
	D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc = {};
	DSVdesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVdesc.Texture2D.MipSlice = 0;
	Debug::logErrorCode(device->CreateDepthStencilView(depthTexture.Get(), &DSVdesc, &DSV));

	context->OMSetRenderTargets(1, target.GetAddressOf(), DSV.Get());

	//update viewport size
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);
}

void Graphics::setFullscreen(bool fullscreen)
{
	Debug::logErrorCode(swap->SetFullscreenState(fullscreen, nullptr));
}

//Update Calls
void Graphics::updateLightData() {

	//get closest point lights
	PointLight* closest[MaxLights];

	//update positions
	Vec3 temp;

	if (directionalLight == nullptr) {
		vsBufferData.lightPos[0] = DirectX::XMVectorSet(0, 0, 0, 0);
	}
	else {
		Vec3 dir = directionalLight->entity->getTransform()->up();
		vsBufferData.lightPos[0] = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 1);
	}

	for (int i = 0; i < MaxLights; i++) {
		if (pointLights.size() <= i) {
			vsBufferData.lightPos[i+1] = DirectX::XMVectorSet(0, 0, 0, 0);
			continue;
		}

		temp = pointLights[i].entity->getTransform()->getPosition();
		vsBufferData.lightPos[i + 1] = DirectX::XMVectorSet(temp.x, temp.y, temp.z, 1);// {temp.x, temp.y, temp.z};
	}

	//update light properties
	if (directionalLight == nullptr)
		psBufferData.dirLightDetails = { 0, 0, 0 };
	else
		psBufferData.dirLightDetails = { directionalLight->Colour.x, directionalLight->Colour.y, directionalLight->Colour.z };

	for (int i = 0; i < MaxLights; i++) {
		if (pointLights.size() <= i) {
			psBufferData.pntLightDetails[i] = { 0, 0, 0 };
			continue;
		}

		temp = pointLights[i].Colour;
		psBufferData.pntLightDetails[i] = { temp.x, temp.y, temp.z };
		psBufferData.pntLightDetails[i].power = pointLights[i].power;
		psBufferData.pntLightDetails[i].range = pointLights[i].range;

	}
}

void Graphics::updatePixelShader()
{
	if (!psBufferCreated) {
		//setup
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(PSBufferData);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &psBufferData;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		//create buffer
		Debug::logErrorCode(device->CreateBuffer(&bufferDesc, &initData, &psBuffer));

		psBufferCreated = true;
	}
	else {
		//get location of buffer
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		memset(&mappedSubResource, 0, sizeof(mappedSubResource));

		Debug::logErrorCode(context->Map(psBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));

		//copy new data
		memcpy(mappedSubResource.pData, &psBufferData, sizeof(PSBufferData));

		//cleanup
		context->Unmap(psBuffer.Get(), 0);
	}

	context->PSSetConstantBuffers(1, 1, psBuffer.GetAddressOf());
}

void Graphics::updateVertexShader()
{
	if (!vsBufferCreated) {
		//setup
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(VSBufferData);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &vsBufferData;
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		//create buffer
		Debug::logErrorCode(device->CreateBuffer(&bufferDesc, &initData, &vsBuffer));

		vsBufferCreated = true;
	}
	else {
		//get location of buffer
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		memset(&mappedSubResource, 0, sizeof(mappedSubResource));

		Debug::logErrorCode(context->Map(vsBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource));

		//copy new data
		memcpy(mappedSubResource.pData, &vsBufferData, sizeof(VSBufferData));

		//cleanup
		context->Unmap(vsBuffer.Get(), 0);
	}

	context->VSSetConstantBuffers(1, 1, vsBuffer.GetAddressOf());
}