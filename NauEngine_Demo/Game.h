#pragma once

#include "GameTimer.h"
#include "Scene.h"
#include "DisplayWindow.h"

#include "ECS/Systems/RenderSystem.h"

#include <memory>

class Game
{
public:
    Game();
    ~Game();

    void Release();
    void Run();

    void Tick(float deltaTime);
    void Render();

    GameTimer timer;

    std::unique_ptr<Scene> scene;

    std::unique_ptr<RenderSystem> renderSystem;

    DisplayWindow displayWindow;

    HINSTANCE hInstance;
    LPCWSTR applicationName;

    int winWidth = 1280;
    int winHeight = 720;

    float deltaTime = 0.0f;

    // Load/save scene
    void LoadScene();
    void SaveScene();



    void HandleKeyDown(Keys key);
    void HandleMouseMove(const InputDevice::MouseMoveEventArgs& args);
};

