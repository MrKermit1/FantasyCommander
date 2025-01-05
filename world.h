#pragma once
#include "terrainnode.h"
#include "raylib.h"
class World
{
public:
	World();
	void Draw();
	void Update();
	void Move();
private:
	TerrainNode** map;
	Camera2D camera;
	void GenerateWorld();
	void GenerateTerrain(TerrainNode::TerrainType type, int ammount);
	float RandomNumber(int min, int max);
	bool CheckTerrain(int x, int y, TerrainNode::TerrainType type);
};

