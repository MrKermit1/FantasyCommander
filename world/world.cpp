#include "world.h"
World::World(){}

World::World(int worldMap[32][24], std::string worldName)
{
	initMap(worldMap);
	this->name = worldName;
}

void World::initMap(int mapBuffer[32][24])
{
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			map[i][j] = mapBuffer[i][j];
		}
	}
}
