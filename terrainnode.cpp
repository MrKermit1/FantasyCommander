#include "terrainnode.h"

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

void TerrainNode::Draw()
{
    DrawTextureV(texture, position, WHITE);
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
