#include <raylib.h>
#include "world/world.h"
#include "world/terrain.h"
#include "creatures/creature.h"
#include <iostream>
#include <random>
#include <cmath>
#include <vector>
constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 800;

Terrain::Type map[64][48];
std::vector<Creature> creatures = {};

float RandomNumber(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max); // przedział losowania [x, y]

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

void GenerateRootWorld()
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            map[i][j] = Terrain::GRASS;
        }
    }
}

void GenerateTerrainElements(Terrain::Type type, int ammount)
{
    //generuj las
    float x = RandomNumber(0, 64 * 25);
    float y = RandomNumber(0, 48 * 25);

    for (int i = 0; i < ammount; i++)
    {
        int xx = ceil(x / 25);
        int yy = ceil(y / 25);

        //jeślij teren to trawa to wstawiaj se co chcesz
        if (CheckTerrain(xx, yy, Terrain::GRASS))
        {
            map[xx][yy] = type;
            map[xx + 1][yy] = type;
            map[xx][yy + 1] = type;
            map[xx + 1][yy + 1] = type;
        }

        //ponowne losowanie (napisac wrapera do tego???)
        x = RandomNumber(0, SCREEN_WIDTH + (SCREEN_WIDTH / 25));
        y = RandomNumber(0, SCREEN_HEIGHT + (SCREEN_WIDTH / 25));
    }
}

void UI()
{
    DrawRectangle(0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, 100, GRAY);
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
    SetTargetFPS(144);

    GenerateRootWorld();
    GenerateTerrainElements(Terrain::FOREST, 70);
    GenerateTerrainElements(Terrain::STONE, 20);
    Creature orc = Creature(Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, Creature::WORKER, Creature::ORC, 0, 0, 0, "sd");
    creatures.push_back(orc);
    World world = World(map, "test", creatures);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        //RENDER
        world.Draw();
        UI();


        world.Move();

        EndDrawing();
    }

    return 0;
}
