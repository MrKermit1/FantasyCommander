#include "building.h"
Building::Building(Type type, Vector2 position, int life, int cost, Resource::Type unit)
{

	switch (type)	
	{
		case Building::BASE:
			texture = LoadTexture("assets/buildings/base.png");
			break;
		case Building::HOUSE:
			break;
		case Building::BARRACKS:
			break;
		default:
			break;
	}

	this->position = position;
	this->life = life;
	this->cost = cost;
	this->costUnit = unit;
}

void Building::Draw()
{
	DrawTextureV(texture, position, WHITE);
}