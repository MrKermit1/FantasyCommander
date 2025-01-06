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

bool TerrainNode::IsClicked()
{
    return clicked;
}

bool TerrainNode::operator==(const TerrainNode& other) const
{
    return this->position.x == other.position.x &&
        this->position.y == other.position.y &&
        this->type == other.type;
}

TerrainNode::TerrainType TerrainNode::GetType()
{
    return this->type;
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
        IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) 
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

void TerrainNode::UnClick()
{
    clicked = false;
}

void TerrainNode::Draw()
{
    DrawTextureV(texture, position, WHITE);
    if (clicked)
    {
        //Draw cross
        DrawLineV(position, {position.x+25.0f, position.y+25.0f }, RED);
        DrawLine(position.x +25.0f, position.y, position.x, position.y+ 25.0f, RED);
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
