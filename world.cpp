#include "world.h"
#include <random>
#include <iostream>
#include "creature.h"
World::World()
{
    map = new TerrainNode* [64];
    for (int i = 0; i < 64; i++)
    {
        map[i] = new TerrainNode[48];
    }

    camera = { 0 };
    camera.target = Vector2{ 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    GenerateWorld();
    GenerateTerrain(TerrainNode::STONE ,100);
    GenerateTerrain(TerrainNode::FOREST ,100);
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
    int x = RandomNumber(0, 62);
    int y = RandomNumber(0,  47);

    for (int i = 0; i < ammount; i++)
    {
        //if terrain is a grass, we can put there any other terrain
        /*if (CheckTerrain(x, y, TerrainNode::GRASS))
        {
            map[x][y].SetType(type);
            map[x + 1][y].SetType(type);
            map[x][y + 1].SetType(type);
            map[x + 1][y + 1].SetType(type);
        }*/

        while (!(CheckTerrain(x, y, TerrainNode::GRASS)))
        {
            x = RandomNumber(0, 62);
            y = RandomNumber(0, 47);
        }

        map[x][y].SetType(type);
        map[x + 1][y].SetType(type);
        map[x][y + 1].SetType(type);
        map[x + 1][y + 1].SetType(type);
    }
}

void World::UnClickUnusedNodes(TerrainNode node)
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            if (!(map[i][j] == node))
            {
                map[i][j].UnClick();
            }
        }
    }
}

void World::UpdateCreatures(Creature creature)
{
    creatures.push_back(creature);
}

int World::RandomNumber(int min, int max)
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
    BeginMode2D(camera);
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            map[i][j].Draw();
        }
    }

    EndMode2D();
}

void World::Update()
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            map[i][j].OnClick(&camera);
            if (map[i][j].IsClicked())
            {
                UnClickUnusedNodes(map[i][j]);
            }
        }
    }
}

void World::Move()
{
    float speed = 10;
    if (IsKeyDown(KEY_W))
    {
        camera.target.y -= speed;
    }

    if (IsKeyDown(KEY_S))
    {
        camera.target.y += speed;
    }

    if (IsKeyDown(KEY_D))
    {
        camera.target.x += speed;
    }

    if (IsKeyDown(KEY_A))
    {
        camera.target.x -= speed;
    }

    camera.zoom += GetMouseWheelMove() * speed / 100.0f;
}
    