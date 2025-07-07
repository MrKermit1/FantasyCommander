#pragma once
#include "player.h"

class UI
{
public:
	UI(int screenWidth, int screenHeight);

	void DrawResources(Player* player);
	void DrawShop();

private:
	int screenWidth;
	int screenHeight;
};

