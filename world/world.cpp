#include "world.h"

World::World()
{
}

World::World(Terrain::Type worldMap[64][48], std::string worldName)
{
	InitMap(worldMap);
	this->name = worldName;
	camera = { 0 };
	camera.target = Vector2{ 0.0f, 0.0f };
	camera.offset = { 0.0f, 0.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

void World::InitMap(Terrain::Type mapBuffer[64][48])
{
	for (int i = 0; i < 64; i++)
	{
		mapPointer[i] = new Terrain[48];
	}

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 48; j++)
		{
			//map[i][j] = mapBuffer[i][j];
			//map[i][j] = Terrain(mapBuffer[i][j], Vector2{ i * 25.0f,  j * 25.0f });
			mapPointer[i][j] = Terrain(mapBuffer[i][j], Vector2{ i * 25.0f,  j * 25.0f });
		}
	}
}

void World::Draw()
{
	BeginMode2D(camera);

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 48; j++)
		{
			//map[i][j].Draw();
			mapPointer[i][j].Draw();
		}
	}

	EndMode2D();
}

void World::Move()
{
	float speed = 10.0f;

	if (IsKeyDown(KEY_UP))
	{
		camera.target.y -= speed;
	}

	if (IsKeyDown(KEY_DOWN))
	{
		camera.target.y += speed;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		camera.target.x += speed;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		camera.target.x -= speed;
	}

	camera.zoom += GetMouseWheelMove() * speed / 2.0f;
}