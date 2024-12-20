#include <raylib.h>
#include "world/world.h"
#include "world/terrain.h"
#include <iostream>
#include <random>
#include <cmath>

constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 800;


Terrain::Type map[64][48];

float RandomNumber(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max); // distribution in range [x, y]

    return dist6(rng);
}

bool CheckTerrain(int x, int y, Terrain::Type type)
{
    return
        map[x][y] == type ||
        map[x + 1][y] == type ||
        map[x][y + 1] == type ||
        map[x + 1][y + 1] == type;
}

void GenerateTerrain(Terrain::Type type, int ammount)
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            map[i][j] = Terrain::GRASS;
        }
    }

    //generate forest
    float x = RandomNumber(0, SCREEN_WIDTH - (SCREEN_WIDTH / 25));
    float y = RandomNumber(0, SCREEN_HEIGHT - (SCREEN_WIDTH / 25));

    for (int i = 0; i < ammount; i++)
    {
        int xx = ceil(x / 25);
        int yy = ceil(y / 25);

        if (CheckTerrain(xx, yy, Terrain::FOREST))
        {
            x = RandomNumber(0, SCREEN_WIDTH - (SCREEN_WIDTH / 25));
            y = RandomNumber(0, SCREEN_HEIGHT - (SCREEN_HEIGHT / 25));
        }
        else
        {
            map[xx][yy] = type;
            map[xx + 1][yy] = type;
            map[xx][yy + 1] = type;
            map[xx + 1][yy + 1] = type;
        }

        //regenarte new random nums
        x = RandomNumber(0, SCREEN_WIDTH - (SCREEN_WIDTH / 25));
        y = RandomNumber(0, SCREEN_HEIGHT - (SCREEN_WIDTH / 25));
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
    GenerateTerrain(Terrain::FOREST, 70);

    World world = World(map, "test");



    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGREEN);
        world.Draw();
        world.Move();

        EndDrawing();
    }
}
