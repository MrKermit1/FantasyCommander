#include "globals.h"
#include "raylib.h"
Player player = Player();
World world = World(&player);

int SizeOfChar(const char* text)
{
	std::string textInString(text);
	return textInString.size();
}

bool IsMouseOnEntity(Vector2 entityPosition, Vector2 entitySize)
{
    Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *(world.GetCamera()));
    return (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
        && mousePosition.x >= entityPosition.x
        && !(mousePosition.x > entityPosition.x + entitySize.x)
        && mousePosition.y >= entityPosition.y
        && !(mousePosition.y > entityPosition.y + entitySize.y)
   );
}
