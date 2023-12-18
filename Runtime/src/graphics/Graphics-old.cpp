#include "Graphics-old.h"

#define checkError(code) if(FAILED(code)) throw std::exception(Debug::TranslateHResult(code).c_str())

Microsoft::WRL::ComPtr<ID3D11DeviceContext> Core::Graphics::context = Microsoft::WRL::ComPtr<ID3D11DeviceContext>();
Microsoft::WRL::ComPtr<ID3D11Device> Core::Graphics::device = Microsoft::WRL::ComPtr<ID3D11Device>();
Microsoft::WRL::ComPtr<IDXGISwapChain> Core::Graphics::swap = Microsoft::WRL::ComPtr<IDXGISwapChain>();

std::vector<Core::MeshRenderer> Core::Graphics::renderers = std::vector<Core::MeshRenderer>();
std::vector<Core::Camera> Core::Graphics::cameras = std::vector<Core::Camera>();
std::vector<Core::PointLight> Core::Graphics::pointLights = std::vector<Core::PointLight>();
std::vector<Core::DirectionalLight> Core::Graphics::dirLights = std::vector<Core::DirectionalLight>();
Core::DirectionalLight* Core::Graphics::directionalLight = nullptr;

int Core::Graphics::width = 0;
int Core::Graphics::height = 0;

Core::Graphics::Graphics() {
}

//update
void Core::Graphics::Start(HWND hwnd, int width, int height)
{
	this->hwnd = hwnd;

	//create device, context, and swap chain
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
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
	frameBuffer.Reset();

	// create depth stencil
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};

	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthState;
	checkError(device->CreateDepthStencilState(&dsDesc, &depthState));
	context->OMSetDepthStencilState(depthState.Get(), 1);
	depthState.Reset();

	//setup transparency
	D3D11_BLEND_DESC BlendStateDescription = CD3D11_BLEND_DESC{ CD3D11_DEFAULT{} };
	ID3D11BlendState* blend;

	BlendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	BlendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendStateDescription.AlphaToCoverageEnable = true;
	BlendStateDescription.IndependentBlendEnable = false;

	device->CreateBlendState(&BlendStateDescription, &blend);

	float blendFactor[] = { 1, 1, 1, 1 };
	context->OMSetBlendState(blend, blendFactor, 0xffffffff);

	//update size of window
	windowedWidth = width;
	windowedHeight = height;
	updateDimensions(width, height);

	//set viewport size
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
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

	checkError(device->CreateSamplerState(&sampleDesc, &sampler));
	context->PSSetSamplers(0, 1, sampler.GetAddressOf());

	shader.Start(device.Get(), context.Get());
}

//Draw Calls
void Core::Graphics::EndFrame()
{
	HRESULT hr;
	context->Flush();
	if (FAILED(hr = swap->Present(1, 0))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			checkError(Graphics::device->GetDeviceRemovedReason());
		else
			Debug::logErrorCode(hr);
	}

	context->ClearRenderTargetView(target.Get(), backgroundColour);
	context->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void Core::Graphics::Draw() {

	//get view matrix
	Camera* cam = Camera::getMainCamera();
	if (cam == nullptr || cam->entity == nullptr || (!cam->exists))
		return;

	DirectX::XMMATRIX viewMat = cam->getViewMatrix();
	DirectX::XMMATRIX posMat = cam->getPositionMatrix();
	Vec3 camPos = cam->entity->transform.getPosition();

	//update buffers
	vsBufferData.camMatrix = posMat * viewMat;
	updateLightData();

	updateVertexShader();
	updatePixelShader();

	//update skybox
	skybox.transform.setPosition(camPos);
	skybox.transform.setRotation(0, 0, 0);
	skybox.transform.setScale(cam->farPlane/2, cam->farPlane/2, cam->farPlane/2);

	//render mesh renderers
	for (int i = 0; i < renderers.size(); i++) {
		
		if (renderers[i].entity == nullptr)
			continue;

		if(renderers[i].exists)
			renderers[i].Draw(device.Get(), context.Get());
		else 
			renderers.erase(renderers.begin() + i);
	}
}

//Component Management
Core::MeshRenderer* Core::Graphics::createMesh(Entity* parent) {
	renderers.emplace_back(parent);
	if (parent)
		parent->addComponent(&renderers[renderers.size() - 1]);
	return &(renderers[renderers.size() - 1]);
}

Core::PointLight* Core::Graphics::createPointLight(Entity* parent) {
	pointLights.emplace_back(parent);
	if (parent)
		parent->addComponent(&pointLights[pointLights.size() - 1]);
	return &pointLights[pointLights.size() - 1];
}

Core::Camera* Core::Graphics::createCamera(Entity* parent) {
	cameras.push_back(Camera(parent));
	if (parent)
		parent->addComponent(&cameras[cameras.size() - 1]);
	return &cameras[cameras.size() - 1];
}

Core::DirectionalLight* Core::Graphics::createDirectionalLight(Entity* parent) {
	dirLights.emplace_back(parent);
	if (parent)
		parent->addComponent(&dirLights[dirLights.size() - 1]);
	setDirectionalLight(&dirLights[dirLights.size() - 1]);
	return &dirLights[dirLights.size() - 1];
}

void Core::Graphics::setDirectionalLight(DirectionalLight* light) {
	directionalLight = light;
}


void Core::Graphics::setSkybox(std::string sides[6])
{
	skybox.removeComponents("MeshRenderer");
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

	psBufferData.ambientLight = { AverageColour[0], AverageColour[1], AverageColour[2],  1 };
	skyboxEnabled = true;
}

void Core::Graphics::setAmbientStrength(float strength)
{
	ambientStrength = strength;
}

void Core::Graphics::setBackgroundColour(float colour[4])
{
	//get rid of skybox
	skybox.removeComponents("MeshRenderer");
	skyboxEnabled = false;

	for (int i = 0; i < 4; i++)
		backgroundColour[i] = colour[i];
}

int Core::Graphics::getWidth()
{
	return width;
}

int Core::Graphics::getHeight()
{
	return height;
}

void Core::Graphics::updateDimensions(int width, int height)
{
	//save new dimensions
	this->width = width;
	this->height = height;

	//update camera
	Camera::viewWidth = width;
	Camera::viewHeight = height;

	DXGI_MODE_DESC dxgiDesc = {};
	dxgiDesc.Width = width;
	dxgiDesc.Height = height;
	dxgiDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	dxgiDesc.RefreshRate.Numerator = 1000;
	dxgiDesc.RefreshRate.Denominator = 1;
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
}

void Core::Graphics::setFullscreen(bool fullscreen)
{
	if (fullscreen) {
		windowedWidth = getWidth();
		windowedHeight = getHeight();

		HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO monitorInfo;
		monitorInfo.cbSize = sizeof(MONITORINFO);
		GetMonitorInfo(hMonitor, &monitorInfo);

		swap->SetFullscreenState(true, nullptr);
		updateDimensions(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);
	}
	else {
		swap->SetFullscreenState(false, nullptr);
		updateDimensions(windowedWidth, windowedHeight);
	}
}

void Core::Graphics::updateLightData() {

	//destroy non existent components
	for (int i = 0; i < dirLights.size(); i++)
		if (!dirLights[i].exists)
			dirLights.erase(dirLights.begin() + i);

	for (int i = 0; i < pointLights.size(); i++)
		if (!pointLights[i].exists)
			pointLights.erase(pointLights.begin() + i);

	//find closest valid point lights
	int closest[MaxLights];
	int skipped = 0;
	Camera* cam = Camera::getMainCamera();
	for (int i = 0; i < max(pointLights.size(), MaxLights + skipped); i++) {
		//for access spots in closest
		if (i >= pointLights.size()) {
			closest[i] = -1;
			continue;
		}

		//skip if not attatched to entity
		if (pointLights[i].entity == nullptr) {
			skipped++;
			continue;
		}
		
		//fill closest with first in list
		if (i < MaxLights + skipped) {
			closest[i] = i;
			continue;
		}

		//replace if closer
		for (int j = 0; j < MaxLights; j++) {
			if (Vec3::distance(pointLights[i].entity->transform.getPosition(), cam->entity->transform.getPosition()) < Vec3::distance(pointLights[closest[j]].entity->transform.getPosition(), cam->entity->transform.getPosition())) {
				closest[j] = i;
				break;
			}
		}
	}

	// update directional light position
	if (directionalLight == nullptr || directionalLight->entity == nullptr) {
		vsBufferData.lightPos[0] = DirectX::XMVectorSet(0, 0, 0, 0);
	}
	else {
		Vec3 dir = directionalLight->entity->transform.up();
		vsBufferData.lightPos[0] = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 1);
	}

	//update point light positions
	for (int i = 0; i < MaxLights; i++) {
		if (closest[i] == -1) {
			vsBufferData.lightPos[i + 1] = DirectX::XMVectorSet(0, 0, 0, 0);
			continue;
		}

		vsBufferData.lightPos[i + 1] = pointLights[closest[i]].entity->transform.getMatrix().r[3];
	}

	//update directional light properties
	if (directionalLight == nullptr || directionalLight->entity == nullptr)
		psBufferData.dirLightDetails = { 0, 0, 0 };
	else
		psBufferData.dirLightDetails = { directionalLight->Colour.x, directionalLight->Colour.y, directionalLight->Colour.z };

	Vec3 temp;
	//update point light properties
	for (int i = 0; i < MaxLights; i++) {
		//if less lights than max
		if (closest[i] == -1) {
			psBufferData.pntLightDetails[i] = { 0, 0, 0 };
			continue;
		}

		//update
		temp = pointLights[closest[i]].Colour;
		psBufferData.pntLightDetails[i] = { temp.x, temp.y, temp.z };
		psBufferData.pntLightDetails[i].power = pointLights[closest[i]].power;
		psBufferData.pntLightDetails[i].range = pointLights[closest[i]].range;
	}
}

void Core::Graphics::updatePixelShader()
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

void Core::Graphics::updateVertexShader()
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