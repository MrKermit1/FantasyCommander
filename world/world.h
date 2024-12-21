#pragma once
#include <iostream>
#include "raylib.h"
#include "terrain.h"
#include <algorithm>

class World
{
private:
	std::string name;
	//Terrain map[64][48];
	Terrain** mapPointer = new Terrain*[64];
	Camera2D camera;

	void InitMap(Terrain::Type mapBuffer[64][48]);

public:
	World();
	World(Terrain::Type mapBuffer[64][48], std::string worldName);

	void Draw();
	void Move();
};

