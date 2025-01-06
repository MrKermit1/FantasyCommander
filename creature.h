#pragma once
#include "raylib.h"
#include <string>
class Creature
{
public:
	static enum Race
	{
		ORC,
		DWARF
	};
	static enum Profession
	{
		WARRIOR,
		WIZARD,
		WORKER
	};

	Creature();
	Creature(Vector2 pos, Creature::Profession proffesion, Creature::Race race);
	bool IsClicked();
	void Draw();
	void OnClick(Camera2D* camera);
	void UnClick();
private:
	Race race;
	Profession proffesion;
	int lifePoints;
	Vector2 position;
	Texture2D texture;
	bool clicked;
	std::string racePath;

	void AssignProffesion();
	void AssignRace();
};

