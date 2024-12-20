#pragma once
#include "raylib.h"
class Terrain
{
private:
	Texture2D texture;
	Vector2 position;
public:
	Terrain();

	static enum Type
	{
		GRASS,
		STONE,
		FOREST
	};

	Terrain(Terrain::Type terrainType, Vector2 pos);
	void Draw();
};

