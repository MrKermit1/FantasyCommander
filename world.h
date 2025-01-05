#pragma once
#include "terrainnode.h"
#include "raylib.h"
class World
{
public:
	World();
	void Draw();
	void Update();
private:
	TerrainNode map[64][48];
	void GenerateWorld();
	void GenerateTerrain(TerrainNode::TerrainType type, int ammount);
	float RandomNumber(int min, int max);
	bool CheckTerrain(int x, int y, TerrainNode::TerrainType type);
};

