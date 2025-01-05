#pragma once
#include "raylib.h"
class TerrainNode
{
public:
	static enum TerrainType
	{
		GRASS,
		FOREST,
		STONE
	};
	TerrainNode();
	TerrainNode(Vector2 pos, TerrainNode::TerrainType type);
	int fCost();
	TerrainType GetType();
	void SetType(TerrainType type);

	void Draw();
private:
	Vector2 position;
	Texture2D texture;
	int gCost;
	int hCost;
	TerrainType type;

	void SwitchTexture();
};

