#include <iostream>
#include "raylib.h"
#include "world.h"
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGTH = 800;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGTH, "Fantasy Commander");
    World world = World();
    while (!WindowShouldClose())
    {
        BeginDrawing();

        //Generate world
        world.Draw();


        EndDrawing();
    }
}