#include "RenderSystem.h"

#include "RenderComponent.h"

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
}

void RenderSystem::RenderScene(const Scene& scene)
{
	/*
	for (auto entity : scene.entities) {
		RenderComponent* renderableEntity = dynamic_cast<RenderComponent*>(entity);
		if (renderableEntity) {
			// Object implements Interface
			renderableEntity->Render();
		}
	}
	*/

	// Passes
	/*
	for (RenderPass* pass : passes) {
		context->ClearState();
		pass->StartFrame();
		pass->Pass(scene);
		pass->EndFrame();
	}
	*/

	swapChain->Present(1, 0);
}

