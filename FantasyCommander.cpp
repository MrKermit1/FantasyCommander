#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "world.h"
#include "player.h"
#include "ui.h"
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
Player player = Player();
UI ui = UI(SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Fantasy Commander");
    SetTargetFPS(60);
    World world = World(&player);

    Creature c = Creature({ 120.0f, 100.0f }, Creature::WARRIOR, Creature::DWARF);
    Creature c2 = Creature({ 150.0f, 100.0f }, Creature::WARRIOR, Creature::DWARF);
	world.AddCreature(c);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        
        world.Update();
        world.Move();
        world.Draw();
        ui.DrawResources(&player);
        ui.DrawShop();

        EndDrawing();
    }

}