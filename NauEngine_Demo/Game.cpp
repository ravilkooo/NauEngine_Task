#include "Game.h"
#include "SimpleEntity.h"
#include <fstream>

Game::Game()
{
	applicationName = L"NauGame";
	hInstance = GetModuleHandle(nullptr);

	winWidth = 1280;
	winHeight = 720;

	timer = GameTimer();
	scene = new Scene();

	displayWindow = DisplayWindow(this, applicationName, hInstance, winWidth, winHeight);

	renderSystem = new RenderSystem(&displayWindow);

	for (size_t i = 0; i < 25; i++)
	{
		scene->AddEntity(new SimpleEntity(renderSystem->GetDevice(), 4 * i * 1));
	}

	json data;
	std::ofstream outfstream("scene.json");
	scene->to_json(data);
	//stuff_to_json(data, Json_stuff({ 4,1,4 }));
	outfstream << std::setw(4) << data << std::endl;
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

Game::~Game()
{
	// TO-DO: Освобождение ресурсов
}
