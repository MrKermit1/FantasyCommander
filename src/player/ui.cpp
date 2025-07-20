#include "ui.h"
#include <string>
#include "raylib.h"
#include "../globals.h"
#include "../entities/buildings/building.h"
UI::UI(int screenWidth, int screenHeight)
{
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
}

void UI::DrawResources()
{
    DrawRectangle(0, 0, screenWidth, 100, GRAY);

    std::string wood = "Wood: ";
    std::string stone = "Stone: ";
    std::string iron = "Iron: ";
    std::string money = "Money: ";

    DrawText(wood.append(std::to_string(player.GetWood())).c_str(), 10, 10, 20, WHITE);
    DrawText(stone.append(std::to_string(player.GetStone())).c_str(), 10, 30, 20, WHITE);
    DrawText(iron.append(std::to_string(player.GetIron())).c_str(), 10, 50, 20, WHITE);
    DrawText(money.append(std::to_string(player.GetMoney())).c_str(), 10, 70, 20, WHITE);
}

void UI::DrawShop()
{
	const int margin = 10;
    DrawRectangle(0, screenHeight - 100, screenWidth, 100, GRAY);
	DrawButton(margin, screenHeight - 60, "Base", 200, 30, []() {
        if (!world.IsAnyBuildingInBuildMode())
        {
            world.AddBuilding(Building({ 0, 0 }, Building::BASE));
            std::cout << "Dodano budynek\n";
        }
	});
}

void UI::DrawButton(int posx, int posy, const char* text, int width, int height, void(*func)())
{
    DrawRectangle(posx, posy, width, height, DARKGRAY);
	DrawText(text, posx + 50, posy + 5, 20, WHITE);
    Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *(world.GetCamera()));

    //onClick section
    if
    (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
        && mousePosition.x >= posx
        && !(mousePosition.x > posx + width)
        && mousePosition.y >= posy
        && !(mousePosition.y > posy + height)
    )
    {
        func();
    }

	
}
