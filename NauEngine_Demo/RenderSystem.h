#pragma once
#include <d3d11.h>
#include <wrl.h>    
#include <directxmath.h>

#include "DisplayWindow.h"
#include "Scene.h"
#include "Camera.h"

//#include "GBuffer.h"

class RenderSystem
{
public:
	RenderSystem(DisplayWindow* displayWin);

	// TO-DO: replace ptr with some smart ptr?
	void RenderScene(const Scene& scene);

	void StartFrame();
	void EndFrame();


	ID3D11Device* GetDevice() { return device.Get(); }
	ID3D11DeviceContext* GetDeviceContext() { return context.Get(); }

	void SetMainCamera(std::shared_ptr<Camera> camera) { this->mainCamera = camera; }
	std::shared_ptr<Camera> GetMainCamera() { return mainCamera; };

	ID3D11Texture2D* GetBackBuffer() { return backBuffer.Get(); }

    // void AddPass(RenderPass* pass);

    // std::vector<RenderPass*> passes;

protected:
	// TO-DO: Com ptr ?
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;

	D3D_FEATURE_LEVEL featureLevels[1] = { D3D_FEATURE_LEVEL_11_1 };

	// TO-DO: Com ptr ?
	DisplayWindow* displayWindow;

	UINT screenWidth = 1280;
	UINT screenHeight = 720;

	// pass stuff
	// TO-DO: Com ptr ?
	ID3D11RenderTargetView* renderTargetView;
	D3D11_VIEWPORT viewport;
	ID3D11Texture2D* pDepthStencil;
	ID3D11DepthStencilView* pDSV;

	// TO-DO: Com ptr ?
	std::shared_ptr<Camera> mainCamera;
};
