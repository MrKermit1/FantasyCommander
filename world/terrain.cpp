#include "terrain.h"
#include "raylib.h"
#include<iostream>
Terrain::Terrain() {}

Terrain::Terrain(Terrain::Type terrainType, Vector2 pos)
{
	switch (terrainType)
	{
		case Terrain::GRASS:
			texture = LoadTexture("assets/terrain/grass.png");
			break;
		case Terrain::STONE:
			texture = LoadTexture("assets/terrain/stone.png");
			break;
		case Terrain::FOREST:
			texture = LoadTexture("assets/terrain/forest.png");
			break;
		default:
			texture = LoadTexture("assets/terrain/grass.png");
			break;
	}

	position = pos;
}

void Terrain::Draw()
{
	DrawTextureV(texture, position, WHITE);
}

void Terrain::OnClick()
{
	Vector2 mousePosition = GetMousePosition();

	if
	(
		(mousePosition.x >= position.x && mousePosition.x <= position.x + 25) &&
		(mousePosition.y >= position.y && mousePosition.y <= position.y + 25)
	)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			//TODO:
			//maybe it should return position of terrain so
			//npc know where to go
		}
	}
}