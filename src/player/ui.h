#pragma once

#include "raylib.h"

class UI
{
public:
	UI(int screenWidth, int screenHeight);

	void DrawResources();
	void DrawShop();

private:
	int screenWidth;
	int screenHeight;
	void DrawButton(Vector2 position, const char* text, Vector2 size, int fontSize, void(*func)());
};

