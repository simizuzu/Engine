#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>

const int window_width = 1280;
const int window_height = 720;

struct WINDOWSIZE
{
	int width = 1280;
	int height = 720;
};

class WinApp
{
	void CreateGameWindow(
		const wchar_t* title = TitleName.data(),
		UINT windowStyle = WS_OVERLAPPEDWINDOW,
		int32_t Width = window_width,
		int32_t Height = window_height);
};

