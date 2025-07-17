#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "globals.h"
#include "player/ui.h"
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main()
{
    SetTargetFPS(60);
    UI ui = UI(SCREEN_WIDTH, SCREEN_HEIGHT);
    Creature c = Creature({ 120.0f, 100.0f }, Creature::WARRIOR, Creature::DWARF);
    Creature c2 = Creature({ 150.0f, 100.0f }, Creature::WARRIOR, Creature::DWARF);

	world.AddCreature(c);
	world.AddCreature(c2);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        
        world.Update();
        world.Move();
        world.Draw();
        ui.DrawResources();
        ui.DrawShop();

        EndDrawing();
    }
}