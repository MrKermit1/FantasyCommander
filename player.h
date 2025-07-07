#pragma once
#include <vector>

class Player
{
public:
	Player();

	int GetWood();
	int GetStone();
	int GetIron();
	int GetMoney();

	void AddToMoney(int n);
	void AddToWood(int n);	
	void AddToStone(int n);
	void AddToIron(int n);

private:
	int money;
	int wood;
	int stone;
	int iron;
};

