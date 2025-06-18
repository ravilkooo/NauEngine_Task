#include "Game.h"
#include "SimpleEntity.h"
#include "PlaneEntity.h"
#include "ResourceManager.h"
#include <fstream>
#include <iostream>

Game::Game()
{
	applicationName = L"NauGame";
	hInstance = GetModuleHandle(nullptr);

	winWidth = 1280;
	winHeight = 720;

	scene = new Scene();

	displayWindow = DisplayWindow(this, applicationName, hInstance, winWidth, winHeight);

	renderSystem = new RenderSystem(&displayWindow);

	int answer = 0;
	std::cout << "New scene (0) or Saved scene (1) ? :";
	std::cin >> answer;

	if (answer)
	{
		json scene_data;
		std::ifstream f("scene.json");
		f >> scene_data;
		f.close();
		scene->from_json(renderSystem->GetDevice(), scene_data);
		renderSystem->SetMainCamera(scene->mainCamera);

		json resources_data;
		f.open("resources.json");
		f >> resources_data;
		f.close();
		ResourceManager::Instance().from_json(renderSystem->GetDevice(), resources_data);
	}
	else {
		for (size_t i = 0; i < 25; i++)
		{
			scene->AddEntity(std::make_unique<SimpleEntity>(renderSystem->GetDevice(), 4 * i * 1));
		}
		scene->AddEntity(std::make_unique<PlaneEntity>(renderSystem->GetDevice()));
		scene->mainCamera = renderSystem->GetMainCamera();
		scene->mainCamera->SetPosition({ 0,0,-10 });

		json data;
		std::ofstream outfstream("scene.json");
		scene->to_json(data);
		outfstream << std::setw(4) << data << std::endl;

		data.clear();
		outfstream.open("resources.json");
		ResourceManager::Instance().to_json(data);
		outfstream << std::setw(4) << data << std::endl;
	}

	timer = GameTimer();

}

void Game::Run()
{
	MSG msg = {};
	bool isExitRequested = false;
	unsigned int frameCount = 0;
	float totalTime = 0;

	while (!isExitRequested) {
		// Handle the windows messages.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			isExitRequested = true;
		}
		timer.Tick();
		deltaTime = timer.GetDeltaTime();
		totalTime += deltaTime;
		frameCount++;

		if (totalTime > 1.0f) {
			float fps = frameCount * 1.0f / totalTime;

			totalTime -= 1.0f;

			WCHAR text[256];
			swprintf_s(text, TEXT("%s, FPS: %f"), applicationName, fps);
			SetWindowText(displayWindow.hWnd, text);

			frameCount = 0;
		}

		Tick(deltaTime);
		Render();
	}
}

void Game::Tick(float deltaTime) {
	scene->Tick(deltaTime);
}

void Game::Render()
{
	renderSystem->RenderScene(*scene);
}

void Game::LoadScene()
{
	json data;
	std::ifstream in_fstream("scene.json");
	scene->from_json(renderSystem->GetDevice(), data);
	renderSystem->SetMainCamera(scene->mainCamera);
}

Game::~Game()
{
	// TO-DO: Освобождение ресурсов
}
