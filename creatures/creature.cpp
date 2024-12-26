#include "creature.h"
#include<iostream>
#include "raylib.h"
#include <string>

Creature::Creature(Vector2 position, Class _class, Race race, int life, int level, float speed, std::string name)
{

	const char* path = "assets/creatures/";
	const char* raceString;

	char fullPath[100] = "";

	strcat_s(fullPath, path);

	switch (race)
	{
		case Creature::ORC:
			raceString = "orcs/";
			strcat_s(fullPath, raceString);
			break;
		case Creature::DWARF:
			raceString = "dwarfs/";
			strcat_s(fullPath, raceString);
			break;
		default:
			break;
	}

	switch (_class)
	{
		case Creature::WORKER:
			strcat_s(fullPath, "/worker.gif");
			texture = LoadTexture(fullPath);
			break;
		case Creature::SOLDIER:
			strcat_s(fullPath, "/soldier.gif");
			break;
		default:
			break;
	}

	this->position = position;
	this->life = life;
	this->level = level;
	this->speed = speed;
	this->name = name;

	this->clicked = false;
	this->order = NONE;
	
	this->_class = _class;
	this->race = race;
}

void Creature::Click()
{
	clicked = !clicked;
}

void Creature::Draw()
{
	DrawTextureV(texture, position, WHITE);
}