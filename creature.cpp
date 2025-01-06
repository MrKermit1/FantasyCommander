#include "creature.h"
#include <iostream>
Creature::Creature()
{
}

Creature::Creature(Vector2 pos, Creature::Profession proffesion, Creature::Race race)
{
	position = pos;
	this->proffesion = proffesion;
	this->race = race;
	clicked = false;
	AssignRace();
	AssignProffesion();

	texture.width = 25;
	texture.height = 25;
}

bool Creature::IsClicked()
{
	return clicked;
}

void Creature::Draw()
{
	DrawTextureV(texture, position, WHITE);
	if (clicked)
	{
		DrawCircleLines(position.x + 12.5f, position.y, 25.0f, BLUE);
	}
}

void Creature::OnClick(Camera2D* camera)
{
	Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
	if
		(
			IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)
			&& mousePosition.x >= position.x
			&& !(mousePosition.x > position.x + 25)
			&& mousePosition.y >= position.y
			&& !(mousePosition.y > position.y + 25)
			)
	{
		clicked = !clicked;
	}
}

void Creature::AssignProffesion()
{
	switch (proffesion)
	{
	case Creature::WARRIOR:
		racePath.append("warrior.gif");
		texture = LoadTexture(racePath.c_str());
		break;
	case Creature::WIZARD:
		racePath.append("wizard.gif");
		texture = LoadTexture(racePath.c_str());
		break;
	case Creature::WORKER:
		racePath.append("worker.gif");
		texture = LoadTexture(racePath.c_str());
		break;
	default:
		break;
	}
	if (texture.id == 0) {
		std::cerr << "Error loading texture: " << racePath << std::endl;
	}
}

void Creature::AssignRace()
{
	switch (race)
	{
	case Creature::ORC:
		racePath = "assets/creatures/orcs/";
		break;
	case Creature::DWARF:
		racePath = "assets/creatures/dwarfs/";
		break;
	default:
		break;
	}
}
