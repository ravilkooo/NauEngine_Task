#include "Game.h"

#include "ECS/Entities/SimpleEntity.h"
#include "ECS/Entities/PlaneEntity.h"
#include "ECS/Entities/CustomEntity.h"

#include "ResourceManager/ResourceManager.h"

#include <d3d11.h>
#include <fstream>
#include <iostream>

using namespace DirectX::SimpleMath;

Game::Game()
{
	applicationName = L"NauGame";
	hInstance = GetModuleHandle(nullptr);

	winWidth = 1280;
	winHeight = 720;

	scene = std::make_unique<Scene>();

	displayWindow = DisplayWindow(this, applicationName, hInstance, winWidth, winHeight);

	renderSystem = std::make_unique<RenderSystem>(&displayWindow);
	scriptingSystem = std::make_unique<ScriptingSystem>();

	std::cout << "Controls:\n";
	std::cout << "- WASD - forward/backward, left/right\n";
	std::cout << "- Q/E - down/up\n";
	std::cout << "- Esc - exit\n";
	std::cout << "- <1> - Save scene\n";
	std::cout << "- <2> - Load last scene\n\n";

	int answer = 0;
	std::cout << "Create new scene (0) or Load saved scene (1) ? :";
	std::cin >> answer;

	if (answer)
	{
		// Deserialization
		LoadScene();
	}
	else {
		// Serialization

		/**
		* ��������� ����� ������� �����
		* Add new Entities HERE
		**/

		// �������� ������
		// Floating cubes
		for (size_t i = 0; i < 25; i++)
		{
			scene->AddEntity(std::make_unique<SimpleEntity>(renderSystem->GetDevice(), 4 * i * 1));
		}

		// �������� ������
		// Floating plane
		scene->AddEntity(std::make_unique<PlaneEntity>(renderSystem->GetDevice()));

		// ��������� ������ - ����� ������ �������, ������� � ��������� �������
		// Cusstom object - you can set initial position, initial scale and initial rotation
		scene->AddEntity(std::make_unique<CustomEntity>(renderSystem->GetDevice(),
			"./Models/horse.obj", "./Textures/horse_Diffuse.dds", "./LuaScripts/eight.lua",
			Vector3(0, 0, 0), Vector3(1, 1, 1), Vector3(0,-XM_PIDIV2,0)));
		scene->AddEntity(std::make_unique<CustomEntity>(renderSystem->GetDevice(),
			"./Models/gamepad.obj", "./Textures/gamepad_Diffuse.dds", "./LuaScripts/rotateY.lua",
			Vector3(10, 0, 0), Vector3(0.03, 0.03, 0.03 ), Vector3(0, 0, 0)));


		scene->mainCamera = renderSystem->GetMainCamera();
		scene->mainCamera->SetPosition({ 0,0,-10 });
	}


	InputDevice::getInstance().OnKeyPressed.AddRaw(this, &Game::HandleKeyDown);
	InputDevice::getInstance().MouseMove.AddRaw(this, &Game::HandleMouseMove);

	timer = GameTimer();

}

Game::~Game()
{
	Release();
}

void Game::Release()
{
	scene->Clear();
	ResourceManager::Instance().Clear();
	InputDevice::getInstance().OnKeyPressed.RemoveAll();
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
			Release();
			break;

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
	scriptingSystem->Update(*scene, deltaTime);
	scene->Tick(deltaTime);
}

void Game::Render()
{
	renderSystem->RenderScene(*scene);
}

void Game::LoadScene()
{
	json resources_data;
	std::ifstream f("resources.json");
	f >> resources_data;
	f.close();
	ResourceManager::Instance().from_json(renderSystem->GetDevice(), resources_data);

	json scene_data;
	f.open("scene.json");
	f >> scene_data;
	f.close();
	scene->from_json(renderSystem->GetDevice(), scene_data);
	renderSystem->SetMainCamera(scene->mainCamera);
}

void Game::SaveScene()
{
	json data;
	std::ofstream outfstream("scene.json");
	scene->to_json(data);
	outfstream << std::setw(4) << data << std::endl;

	data.clear();
	outfstream.open("resources.json");
	ResourceManager::Instance().to_json(data);
	outfstream << std::setw(4) << data << std::endl;
}

void Game::HandleKeyDown(Keys key) {
	if (key == Keys::E)
	{
		renderSystem->GetMainCamera()->MoveUp(deltaTime * 10.0f);
	}
	if (key == Keys::Q)
	{
		renderSystem->GetMainCamera()->MoveDown(deltaTime * 10.0f);
	}
	if (key == Keys::W)
	{
		renderSystem->GetMainCamera()->MoveForward(deltaTime * 10.0f);
	}
	if (key == Keys::S)
	{
		renderSystem->GetMainCamera()->MoveBackward(deltaTime * 10.0f);
	}
	if (key == Keys::A)
	{
		renderSystem->GetMainCamera()->MoveLeft(deltaTime * 10.0f);
	}
	if (key == Keys::D)
	{
		renderSystem->GetMainCamera()->MoveRight(deltaTime * 10.0f);
	}

	if (key == Keys::D1)
	{
		SaveScene();
	}
	if (key == Keys::D2)
	{
		LoadScene();
	}
}


void Game::HandleMouseMove(const InputDevice::MouseMoveEventArgs& args)
{
	renderSystem->GetMainCamera()->RotateYaw(deltaTime * args.Offset.x * 0.2);
	renderSystem->GetMainCamera()->RotatePitch(-deltaTime * args.Offset.y * 0.2);
}