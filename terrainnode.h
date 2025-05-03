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
	bool IsClicked();
	bool IsWalkable();
	bool operator==(const TerrainNode& other) const;

	Vector2 OnClick(Camera2D* camera);
	TerrainType GetType();
	Vector2 GetPosition();

	void SetType(TerrainType type);
	void SetPosition(Vector2 pos);
	void UnClick();
	void Draw();
private:
	int gCost;
	int hCost;
	bool clicked;
	bool walkable;

	Vector2 position;
	Texture2D texture;
	TerrainType type;

	void SwitchTexture();
};

