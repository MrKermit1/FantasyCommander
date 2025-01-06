#include <iostream>
#include <vector>
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

    Creature c = Creature({ 120.0f, 100.0f }, Creature::WARRIOR, Creature::DWARF);

    World world = World();
    world.UpdateCreatures(c);
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