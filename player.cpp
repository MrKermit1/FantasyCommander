#include "player.h"

Player::Player()
{
	wood = 100;
	stone = 100;
	iron = 0;
	money = 100;
}

int Player::GetWood()
{
	return wood;
}

int Player::GetStone()
{
	return stone;
}

int Player::GetIron()
{
	return iron;
}

int Player::GetMoney()
{
	return money;
}

void Player::AddToMoney(int n)
{
	money += n;
}

void Player::AddToWood(int n)
{
	wood += n;
}

void Player::AddToStone(int n)
{
	stone += n;
}

void Player::AddToIron(int n)
{
	iron += n;
}

