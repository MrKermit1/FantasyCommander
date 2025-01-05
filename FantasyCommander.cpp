#include <iostream>
#include "raylib.h"
#include "world.h"
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;



void UI()
{
    DrawRectangle(0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, 100, GRAY);
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Fantasy Commander");
    SetTargetFPS(60);
    World world = World();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        //DRAWING
        ClearBackground(BLACK);
        world.Draw();
        UI();
        //CATCHING EVENTS AND GENERALLY UPDATE THINGS
        world.Update();
        world.Move();

        EndDrawing();
    }
}