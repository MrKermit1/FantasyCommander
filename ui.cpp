#include "ui.h"
#include <string>
#include "raylib.h"
UI::UI(int screenWidth, int screenHeight)
{
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
}

void UI::DrawResources(Player* player)
{
    DrawRectangle(0, 0, screenWidth, 100, GRAY);

    std::string wood = "Wood: ";
    std::string stone = "Stone: ";
    std::string iron = "Iron: ";
    std::string money = "Money: ";

    DrawText(wood.append(std::to_string(player->GetWood())).c_str(), 10, 10, 20, WHITE);
    DrawText(stone.append(std::to_string(player->GetStone())).c_str(), 10, 30, 20, WHITE);
    DrawText(iron.append(std::to_string(player->GetIron())).c_str(), 10, 50, 20, WHITE);
    DrawText(money.append(std::to_string(player->GetMoney())).c_str(), 10, 70, 20, WHITE);
}

void UI::DrawShop()
{
    DrawRectangle(0, screenHeight - 100, screenWidth, 100, GRAY);
}
