#pragma once
#include <iostream>
#include "raylib.h"
#include "terrain.h"
#include <algorithm>
#include <vector>
#include "../creatures/creature.h"

class World
{
private:
	std::string name;
	//Terrain map[64][48];
	Terrain** mapPointer = new Terrain*[64];
	Camera2D camera;
	std::vector<Creature> creatures;
	void InitMap(Terrain::Type mapBuffer[64][48]);

public:
	World();
	World(Terrain::Type mapBuffer[64][48], std::string worldName, std::vector<Creature> creatures);

	void Draw();
	void Move();
};

