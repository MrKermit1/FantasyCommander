#pragma once
class UI
{
public:
	UI(int screenWidth, int screenHeight);

	void DrawResources();
	void DrawShop();

private:
	int screenWidth;
	int screenHeight;
	void DrawButton(int posx, int posy, const char* text, int width, int height, void(*func)());
};

