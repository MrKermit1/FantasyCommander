#pragma once
#include "terrainnode.h"
#include "raylib.h"
#include "creature.h"
#include <vector>
class World
{
public:
	World();
	void Draw();
	void Update();
	void Move();
	void UpdateCreatures(Creature creature);
private:
	TerrainNode** map;
	Camera2D camera;
	std::vector<Creature> creatures;
	void GenerateWorld();
	void GenerateTerrain(TerrainNode::TerrainType type, int ammount);
	void UnClickUnusedNodes(TerrainNode node);
	float RandomNumber(int min, int max);
	bool CheckTerrain(int x, int y, TerrainNode::TerrainType type);
};

