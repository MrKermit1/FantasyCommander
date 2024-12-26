#pragma once
#include <iostream>
#include "raylib.h"
#include "../resources/resource.h"
class Building
{
private:
	Vector2 position;
	Texture2D texture;
	//std::string name; 
	int life;
	int cost;
	Resource::Type costUnit;
public:
	static enum Type
	{
		BASE,
		HOUSE,
		BARRACKS
	};

	Building(Type type, Vector2 position, int life, int cost, Resource::Type unit);
	void Draw();
};

