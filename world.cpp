#include "world.h"
#include <random>

World::World()
{
    GenerateWorld();
    GenerateTerrain(TerrainNode::STONE ,20);
    GenerateTerrain(TerrainNode::FOREST ,20);
}


void World::GenerateWorld()
{
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 48; j++)
		{
			map[i][j] = TerrainNode(Vector2{i * 25.0f, j * 25.0f}, TerrainNode::GRASS);
		}
	}
}

void World::GenerateTerrain(TerrainNode::TerrainType type, int ammount)
{
    float x = RandomNumber(0, 64 * 25);
    float y = RandomNumber(0, 48 * 25);

    for (int i = 0; i < ammount; i++)
    {
        int xx = ceil(x / 25);
        int yy = ceil(y / 25);

        //if terrain is a grass, we can put there any other terrain
        if (CheckTerrain(xx, yy, TerrainNode::GRASS))
        {
            map[xx][yy].SetType(type);
            map[xx + 1][yy].SetType(type);
            map[xx][yy + 1].SetType(type);
            map[xx + 1][yy + 1].SetType(type);
        }

        x = RandomNumber(0, GetScreenWidth() + (GetScreenWidth() / 25));
        y = RandomNumber(0, GetScreenHeight() + (GetScreenWidth() / 25));
    }
}

float World::RandomNumber(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);

    return dist6(rng);
}

bool World::CheckTerrain(int x, int y, TerrainNode::TerrainType type)
{
    return
        map[x][y].GetType() == type ||
        map[x + 1][y].GetType() == type ||
        map[x][y + 1].GetType() == type ||
        map[x + 1][y + 1].GetType() == type;
}


void World::Draw()
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            map[i][j].Draw();
        }
    }
}
    