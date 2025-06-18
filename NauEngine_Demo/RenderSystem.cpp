#include "RenderSystem.h"

#include "RenderComponent.h"
#include "TransformComponent.h"

RenderSystem::RenderSystem(DisplayWindow* displayWin)
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	this->displayWindow = displayWin;
	screenWidth = displayWin->screenWidth;
	screenHeight = displayWin->screenHeight;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = displayWin->hWnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		nullptr,
		&context);
	if (FAILED(hr))
		throw std::runtime_error("Failed to create Device with Swap Chain");

	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (FAILED(hr))
		throw std::runtime_error("Failed to get back buffer");

	// Pass stuff

	// rtv
	hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView);
	if (FAILED(hr))
		throw std::runtime_error("Failed to create Render Target View");

	// depth buffer
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = screenWidth;
	descDepth.Height = screenHeight;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	device->CreateTexture2D(&descDepth, nullptr, pDepthStencil.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	device->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV);

	viewport = {};
	viewport.Width = static_cast<float>(screenWidth);
	viewport.Height = static_cast<float>(screenHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	mainCamera = std::make_shared<Camera>(device.Get(), screenWidth * 1.0f / screenHeight);
}

void RenderSystem::RenderScene(const Scene& scene)
{
	StartFrame();
	for (auto&	 entity : scene.entities) {
		// std::cout << "?\n";
		if (entity->HasComponent<RenderComponent>()
			&& entity->HasComponent<TransformComponent>())
		{
			auto& transform = entity->GetComponent<TransformComponent>();
			auto& render = entity->GetComponent<RenderComponent>();
			transform.Bind(GetDeviceContext());
			render.Render(GetDeviceContext());
		}
	}
	EndFrame();

	swapChain->Present(1, 0);
}

void RenderSystem::StartFrame()
{
	context->OMSetRenderTargets(1u, &renderTargetView, pDSV.Get());
	float color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, color);
	context->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	context->RSSetViewports(1, &viewport);

	// bind camera const buffer
	mainCamera->UpdateBuffer(GetDeviceContext());
	mainCamera->cameraBuffer->Bind(GetDeviceContext());
}

void RenderSystem::EndFrame()
{
	ID3D11ShaderResourceView* nullSRVs[] = { nullptr };
	context->PSSetShaderResources(0, 1, nullSRVs);
	ID3D11RenderTargetView* nullRTVs[] = { nullptr };
	context->OMSetRenderTargets(1, nullRTVs, nullptr);
}

