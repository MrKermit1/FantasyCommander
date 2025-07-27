#pragma once
#include "world/world.h"
#include "player/player.h"
#include <iostream>
extern Player player;
extern World world;

int SizeOfChar(const char* text);
bool IsMouseOnEntity(Vector2 entityPosition, Vector2 entitySize);