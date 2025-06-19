#pragma once

#include "GameTimer.h"
#include "Scene.h"
#include "RenderSystem.h"
#include "DisplayWindow.h"

class Game
{
public:
    Game();
    ~Game();

    void Run();

    void Tick(float deltaTime);
    void Render();

    GameTimer timer;

    // TO-DO: smart pointer ?
    Scene* scene;

    // TO-DO: smart pointer ?
    RenderSystem* renderSystem;

    // TO-DO: smart pointer ?
    DisplayWindow displayWindow;

    HINSTANCE hInstance;
    LPCWSTR applicationName;

    int winWidth = 1280;
    int winHeight = 720;

    float deltaTime = 0.0f;

    // Load/save scene
    void LoadScene();
};

