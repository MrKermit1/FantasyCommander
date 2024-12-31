#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../world/terrain.h"
#include "raylib.h"
#include "creature.h"

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

void Creature::OnClick(Camera2D camera)
{
	Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);		

	if
	(
		(mousePosition.x >= position.x && mousePosition.x <= position.x + 25) &&
		(mousePosition.y >= position.y && mousePosition.y <= position.y + 25)
	)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			
			//TODO:
			//maybe it should return position of terrain so
			//npc know where to go
			std::cout << position.x << " , " << position.y << "\n";
			clicked = !clicked;
		}
	}

}

void Creature::Draw()
{
	if (clicked)
	{
		DrawCircle(position.x + 18, position.y + 18, 10, BLUE);
		DrawTextureV(texture, position, WHITE);
	}
	else
	{
		DrawTextureV(texture, position, WHITE);
	}
}

std::vector<Terrain> Creature::GetNearNodes(Terrain node,Terrain **mapCopy)
{
	std::vector<Terrain> nearNodes;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}
			else
			{
				int checkX = node.GetPosition().x + i;
				int checkY = node.GetPosition().y + j;

				if (checkX >= 0 && checkX < 64 && checkY >= 0 && checkY < 48)
				{
					nearNodes.push_back(mapCopy[checkX][checkY]);
				}
			}
		}
	}

	return nearNodes;
}

int Creature::GetDistanceToTarget(Terrain nodeA, Terrain nodeB)
{
	int distX = abs(nodeA.GetPosition().x - nodeB.GetPosition().x);
	int distY = abs(nodeA.GetPosition().y - nodeB.GetPosition().y);

	if (distX > distY)
	{
		return 14 * (distY)+10 * (distX - distY);
	}

	return 14 * (distX)+10 * (distY - distX);
}

void Creature::RetracePathNode(Terrain startNode, Terrain endNode)
{
	std::vector<Terrain> path;
	Terrain currentNode = endNode;

	while (!(currentNode == startNode))
	{
		path.push_back(currentNode);
		currentNode = *currentNode.GetParent();
	}

	//reverse
	std::reverse(path.begin(), path.end());


}

bool Creature::IsClicked()
{
	return clicked;
}

Vector2 Creature::GetPosition()
{
	return position;
}

void Creature::GoToTarget(Vector2 target, Terrain startNode, Terrain endNode, Terrain** mapCopy)
{ 
	//A*
	std::vector<Terrain>open;
	std::vector<Terrain>closed;

	open.push_back(startNode);

	int cnt = -1;

	while (open.size() > 0)
	{
		Terrain currentNode = open[0];
		for (int i = 0; i < open.size(); i++)
		{
			if (open[i].fCost() < currentNode.fCost() || open[i].fCost() == currentNode.fCost() && open[i].hCost < currentNode.hCost)
			{
				currentNode = open[i];
			}
		}

		//it will delete currentNode from vector (it looks like shit but its not my fault)
		open.erase(std::remove(open.begin(), open.end(), currentNode), open.end());
		closed.push_back(currentNode);
		
		if (currentNode == endNode)
		{
			RetracePathNode(startNode, endNode);
			return;
		}

		std::vector<Terrain>::iterator it;

		for (auto& near : GetNearNodes(currentNode, mapCopy))
		{
			//look if near node exist in closed nodes
			it = std::find(closed.begin(), closed.end(), near);
												 
			//it != closed.end() it will check if 'if' exist
			if (near.GetType() != Terrain::GRASS || it != closed.end())
			{
				continue;
			}

			int movementCostToNear = currentNode.gCost + GetDistanceToTarget(currentNode, near);

			it = std::find(open.begin(), open.end(), near);

			if (movementCostToNear < near.gCost || !(it != open.end()))
			{
				near.gCost = movementCostToNear;
				near.hCost = GetDistanceToTarget(near, endNode);
				near.SetParent(&currentNode);

				if (!(it != open.end()))
				{
					open.push_back(near);
				}
			}
		}
		
		
	}
}