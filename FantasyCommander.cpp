#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "world.h"
#include "player.h"
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
Player player = Player();

void UI()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, 100, GRAY);

    std::string wood = "wood: ";
    std::string stone = "stone: ";
    std::string iron = "iron: ";
    std::string money = "money: ";

    DrawText(wood.append(std::to_string(player.getWood())).c_str(), 10, 10, 20, WHITE);
    DrawText(stone.append(std::to_string(player.getStone())).c_str(), 10, 30, 20, WHITE);
    DrawText(iron.append(std::to_string(player.getIron())).c_str(), 10, 50, 20, WHITE);
    DrawText(money.append(std::to_string(player.getMoney())).c_str(), 10, 70, 20, WHITE);

    DrawRectangle(0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, 100, GRAY);
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Fantasy Commander");
    //ToggleFullscreen();
    SetTargetFPS(60);

    Creature c = Creature({ 120.0f, 100.0f }, Creature::WARRIOR, Creature::DWARF);

    World world = World();
    world.UpdateCreatures(c);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        world.Update();
        world.Move();
        world.Draw();
        UI();

        EndDrawing();
    }

}