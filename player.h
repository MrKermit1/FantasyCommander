#pragma once
#include <vector>
#include "creature.h"
class Player
{
public:
	int getWood();
	int getStone();
	int getIron();
	int getMoney();

	void AddToMoney(int n);
	void AddToWood(int n);
	void AddToStone(int n);
	void AddToIron(int n);

private:
	int money;
	int wood;
	int stone;
	int iron;

	std::vector<Creature> creatures;
};

