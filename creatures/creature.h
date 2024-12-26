#pragma once
#include "raylib.h"
#include <iostream>
class Creature
{
public:
	static enum Order
	{
		NONE,
		BUILD,
		ATTACK,
		WALK
	};

	static enum Class
	{
		WORKER,
		SOLDIER
	};

	static enum Race
	{
		ORC,
		DWARF
	};
	Creature(Vector2 position, Class _class, Race race, int life, int level, float speed, std::string name);
	void Click();

	void Draw();
	void Move();

private:
	Vector2 position;
	Texture2D texture;
	int life;//maybe i should use __int8, cause we dont need more than 100
	std::string name;
	int level;
	float speed;
	bool clicked;
	Order order;
	Class _class;
	Race race;
};

