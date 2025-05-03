#pragma once
#include "terrainnode.h"
#include "raylib.h"
#include "creature.h"
#include "player.h"
#include <vector>
class World
{
public:
	World();

	std::vector<Vector2> FindPath(Vector2 startPos, Vector2 targetPos);

	void Draw();
	void Update();
	void Move();
	void UpdateCreatures(Creature creature);
private:
	int RandomNumber(int min, int max);
	bool CheckTerrain(int x, int y, TerrainNode::TerrainType type);

	TerrainNode** map;
	Camera2D camera;
	Player player;
	Vector2 FindNearestWalkableNode(Vector2 startPos);
	std::vector<Creature> playerCreatures;

	void GenerateWorld();
	void GenerateTerrain(TerrainNode::TerrainType type, int ammount);
	void UnclickUnusedNodes(TerrainNode node);
	void WalkingOnNode(TerrainNode *node, Creature& creature, Vector2 target);
};

