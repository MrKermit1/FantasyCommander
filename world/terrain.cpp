#include "terrain.h"

Terrain::Terrain() {}

Terrain::Terrain(Terrain::Type terrainType, Vector2 pos)
{
	switch (terrainType)
	{
	case Terrain::GRASS:
		texture = LoadTexture("assets/grass.png");
		break;
	case Terrain::STONE:
		break;
	case Terrain::FOREST:
		texture = LoadTexture("assets/forest.png");
		break;
	default:
		texture = LoadTexture("assets/grass.png");
		break;
	}

	position = pos;
}

void Terrain::Draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
}