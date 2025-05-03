#include "creature.h"
#include <iostream>
#include <queue>
#include "raymath.h"
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
	speed = 100.0f;
	//animation
	currentAnimFrame = 0;
	frameDelay = 10;
	frameCounter = 0;
	animFrames = 0;
	nextFrameDataOffset = 0;
	imCreatureAnim = LoadImageAnim(racePath.c_str(), &animFrames);
	texture = LoadTextureFromImage(imCreatureAnim);

	//filters
	SetTextureFilter(texture, TEXTURE_FILTER_POINT);
	SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
}

bool Creature::IsClicked()
{
	return clicked;
}

void Creature::Draw()
{	
	if (clicked)
	{
		DrawCircle(position.x + 15, position.y + 15, 15.0f, BLUE);
	}
	DrawTextureV(texture, position, WHITE);
}

void Creature::OnClick(Camera2D* camera)
{
	Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
	if
	(
			IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
			&& mousePosition.x >= position.x
			&& !(mousePosition.x > position.x + 25)
			&& mousePosition.y >= position.y
			&& !(mousePosition.y > position.y + 25)
	)
	{
		clicked = !clicked;
		std::cout << clicked << "\n";
	}
}

void Creature::UnClick()
{
	clicked = false;
}

void Creature::SetNearestTraget(Vector2 pos)
{
	nearestTarget = pos;
}

void Creature::SetPath(const std::vector<Vector2>& newPath)
{
	path = newPath;
}

void Creature::SetTargetNode(TerrainNode* node)
{
	targetNode = node;
}

bool Creature::IsMoving() const
{
	return !path.empty();
}

void Creature::Animate()
{
	frameCounter++;
	if (frameCounter >= frameDelay)
	{
		currentAnimFrame++;
		std::cout << "Frames loaded: " << animFrames << std::endl;
		std::cout << "Image size: " << imCreatureAnim.width << "x" << imCreatureAnim.height << std::endl;
		std::cout << "Current frame: " << currentAnimFrame << std::endl;
		std::cout << "Next frame data offset: " << nextFrameDataOffset << std::endl;

		if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

		nextFrameDataOffset = imCreatureAnim.width * imCreatureAnim.height * 4 * currentAnimFrame;	
		UpdateTexture(texture, ((unsigned char*)imCreatureAnim.data) + nextFrameDataOffset);

		frameCounter = 0;
	}
}

void Creature::UpdateMovement(float deltaTime)
{
	if (nearestTarget.x == position.x && nearestTarget.y == position.y)
	{
		targetNode->SetType(TerrainNode::GRASS);
	}

	if (!path.empty())
	{
		Vector2 target = path.front();
		Vector2 direction = Vector2Subtract(target, position);
		float distance = Vector2Length(direction);

		if (distance < 1.0f)
		{
			position = target;
			path.erase(path.begin());
		}
		else
		{
			direction = Vector2Normalize(direction);
			position.x += direction.x * speed * deltaTime;
			position.y += direction.y * speed * deltaTime;
		}
	}
}

void Creature::AssignProffesion()
{
	switch (proffesion)
	{
	case Creature::WARRIOR:
		racePath.append("warrior.gif");
		break;
	case Creature::WIZARD:
		racePath.append("wizard.gif");
		break;
	case Creature::WORKER:
		racePath.append("worker.gif");
		break;
	default:
		break;
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

Vector2 Creature::GetPosition()
{
	return position;
}

void Creature::SetPosition(Vector2 pos)
{
	position = pos;
}
