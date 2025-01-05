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
	Vector2 OnClick(Camera2D* camera);
	void Draw();
private:
	Vector2 position;
	Texture2D texture;
	int gCost;
	int hCost;
	TerrainType type;
	bool clicked;
	void SwitchTexture();
};

