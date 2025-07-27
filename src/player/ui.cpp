#include "ui.h"
#include <string>
#include "raylib.h"
#include "../globals.h"
#include "../entities/buildings/building.h"
#include <iostream>

UI::UI(int screenWidth, int screenHeight)
{
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
}

//  ----------------------------------------------------------------

void UI::DrawResources()
{
    Vector2 position = { 0, 0 };
    Vector2 size = { screenWidth, 100 };

    DrawRectangleV(position, size, GRAY);

    std::string wood = "Wood: ";
    std::string stone = "Stone: ";
    std::string iron = "Iron: ";
    std::string money = "Money: ";

    int textPosX = 10;
    int textPosY = 10;
    int margin = 0;
    int fontSize = 20;

    const char* resourcesTextToDisplay[4] =
    {
        wood.append(std::to_string(player.GetWood())).c_str(),
        stone.append(std::to_string(player.GetStone())).c_str(),
        iron.append(std::to_string(player.GetIron())).c_str(),
        money.append(std::to_string(player.GetMoney())).c_str()
    };

    for (const char* text : resourcesTextToDisplay)
    {
        DrawText(text, textPosX, textPosY + margin, fontSize, WHITE);
        margin += 20;
    }
}

//  ----------------------------------------------------------------

void UI::DrawShop()
{
    const int margin = 10;
    const char* text = "Base and other";
    float textSize = SizeOfChar(text);
    const int fontSize = 20;

    const float x = 0.65f;

    Vector2 position = { 0, screenHeight - 100 };
    Vector2 size = { screenWidth, 100 };

    Vector2 buttonPosition = { margin, (float)screenHeight - 60 };
    Vector2 buttonSize = { (textSize * fontSize) * x, 30 };

    

    DrawRectangleV(position, size, GRAY);
    DrawButton(buttonPosition, text, buttonSize, fontSize, []() {
        if (!world.IsAnyBuildingInBuildMode())
        {
            world.AddBuilding(Building({ 0, 0 }, Building::BASE));
            std::cout << "Dodano budynek\n";
        }
	});
}

//  ----------------------------------------------------------------

void UI::DrawButton(Vector2 position, const char* text, Vector2 size, int fontSize, void(*func)())
{
    DrawRectangleV(position, size, DARKGRAY);
    DrawText(text, position.x, position.y, fontSize, WHITE);
    Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *(world.GetCamera()));
    
    if (IsMouseOnEntity(position, size))
    {
        func();
    }	
}
