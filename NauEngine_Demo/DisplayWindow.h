#pragma once

#include <windows.h>
#include <iostream>
#include "InputDevice/InputDevice.h"

class DisplayWindow
{
	friend class Game;

public:
	UINT screenWidth = 1280;
	UINT screenHeight = 720;
	HWND hWnd;

	DisplayWindow();
	DisplayWindow(Game* inGame, LPCWSTR applicationName, HINSTANCE hInstance, int screenWidth, int screenHeight);

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

};
