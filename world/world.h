#pragma once
#include <iostream>
class World
{
private:
	std::string name;
	int map[32][24];

	void initMap(int mapBuffer[32][24]);

public:
	World();
	World(int mapBuffer[32][24], std::string worldName);
};

