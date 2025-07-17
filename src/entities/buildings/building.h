#pragma once
#include <iostream>
#include "raylib.h"
class Building
{
public:
	enum BuildingType
	{
		BASE,
		SAWMILL,
	};

	Building(Vector2 pos, BuildingType type);
	void Draw();
	void Build();
	void Update();
private: 
	bool clicked;
	bool buildMode;

	Vector2 position;
	Texture2D texture;
	BuildingType type;
	void SwitchTexture();
};

