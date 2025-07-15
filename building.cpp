#include "building.h"

Building::Building(Vector2 pos, BuildingType type)
{
	position = pos;
	this->type = type;
	buildMode = true;
	SwitchTexture();
}

void Building::Build()
{
	buildMode = true;
}

void Building::Draw(Camera2D* camera)
{
	if (buildMode)
	{
		Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
		mousePosition.x -= texture.width / 2;
		mousePosition.y -= texture.height / 2;
		DrawTextureV(texture, mousePosition, WHITE);
	}
	else
	{
		DrawTextureV(texture, position, WHITE);
	}
}

void Building::SwitchTexture()
{
	switch (type)
	{
	case Building::BASE:
		texture = LoadTexture("assets/buildings/base.png");
		break;
	case Building::SAWMILL:
		texture = LoadTexture("assets/buildings/sawmill.png");
		break;
	default:
		break;
	}
}