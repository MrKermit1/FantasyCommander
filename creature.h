#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include "terrainnode.h"

class Creature
{
public:
	static enum Race
	{
		ORC,
		DWARF
	};
	static enum Profession
	{
		WARRIOR,
		WIZARD,
		WORKER
	};

	Creature();
	Creature(Vector2 pos, Creature::Profession proffesion, Creature::Race race);
	bool IsClicked();
	bool IsMoving() const;
	Vector2 GetPosition();

	void Draw();
	void OnClick(Camera2D* camera);
	void UnClick();
	void SetPosition(Vector2 pos);
	void SetNearestTraget(Vector2 pos);
	void SetPath(const std::vector<Vector2>& newPath);
	void SetTargetNode(TerrainNode* node);
	void UpdateMovement(float deltaTime);
	void Animate();
private:
	int lifePoints;
	int currentAnimFrame;
	int frameDelay;
	int frameCounter;
	int animFrames ;
	unsigned int nextFrameDataOffset;
	float speed;
	bool clicked;

	Image imCreatureAnim;
	Race race;
	Profession proffesion;
	Vector2 position;
	Vector2 nearestTarget;
	Texture2D texture;
	TerrainNode* targetNode;
	std::vector<Vector2> path;
	std::string racePath;

	void AssignProffesion();
	void AssignRace();
};

