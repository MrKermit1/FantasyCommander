#pragma once
#include "terrainnode.h"
#include "raylib.h"
#include "../entities/creatures/creature.h"
#include "../player/player.h"
#include "../entities/buildings/building.h"
#include <vector>
class World
{
public:
	World();
	World(Player* player);
	std::vector<Vector2> FindPath(Vector2 startPos, Vector2 targetPos);
	Camera2D* GetCamera();
	void Draw();
	void Update();
	void Move();
	void AddCreature(Creature creature);
	void AddBuilding(Building building);
	void GenerateWorld();
	void GenerateTerrain(TerrainNode::TerrainType type, int ammount);
private:
	int RandomNumber(int min, int max);
	bool CheckTerrain(int x, int y, TerrainNode::TerrainType type);
	bool CheckCreatureNodePosition(Vector2 pos);
	Player* player;
	TerrainNode** map;
	Camera2D camera;
	Vector2 currentTarget;
	Vector2 FindNearestWalkableNode(Vector2 startPos);
	std::vector<Creature> playerCreatures;
	std::vector<Building> playerBuildings;

	void UnclickUnusedNodes(TerrainNode node);
	void WalkingOnNode(TerrainNode *node, Creature& creature, Vector2 target);
	void InitGame();
};

