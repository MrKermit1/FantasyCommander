#include "terrainnode.h"
#include <iostream>
TerrainNode::TerrainNode()
{
}

TerrainNode::TerrainNode(Vector2 pos, TerrainNode::TerrainType type)
{
    position = pos;
    this->type = type;

    SwitchTexture();
}

int TerrainNode::fCost()
{
    return 0;
}

TerrainNode::TerrainType TerrainNode::GetType()
{
    return type;
}

void TerrainNode::SetType(TerrainType type)
{
    this->type = type;
    SwitchTexture();
}

Vector2 TerrainNode::OnClick(Camera2D *camera)
{
    Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);

    if 
    (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
        && mousePosition.x >= position.x
        && !(mousePosition.x > position.x+25)
        && mousePosition.y >= position.y
        && !(mousePosition.y > position.y + 25)
    )
    {
        std::cout << "x:" << position.x << " y:" << position.y << "\n";
        clicked = !clicked;
        return position;
    }
}

void TerrainNode::Draw()
{
    DrawTextureV(texture, position, WHITE);
    if (clicked)
    {
        //Draw cross
        DrawLineV(position, {position.x+25, position.y+25}, RED);
        DrawLineV({ position.x + 25, position.y + 25 }, position, RED);
    }
}

void TerrainNode::SwitchTexture()
{
    switch (type)
    {
    case TerrainNode::GRASS:
        texture = LoadTexture("assets/terrain/grass.png");
        break;
    case TerrainNode::FOREST:
        texture = LoadTexture("assets/terrain/forest.png");
        break;
    case TerrainNode::STONE:
        texture = LoadTexture("assets/terrain/stone.png");
        break;
    default:
        break;
    }
}
