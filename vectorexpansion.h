#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "terrainnode.h"

bool ContainsTerrain(std::vector<TerrainNode> *vector, TerrainNode node)
{
	return (std::find(vector->begin(), vector->end(), node) != vector->end());
}

