#include "player.h"

Player::Player()
{
	wood = 100;
	stone = 100;
	iron = 0;
	money = 100;
}

int Player::getWood()
{
	return wood;
}

int Player::getStone()
{
	return stone;
}

int Player::getIron()
{
	return iron;
}

int Player::getMoney()
{
	return money;
}

std::vector<Creature> Player::getCreatures()
{
	return creatures;
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
