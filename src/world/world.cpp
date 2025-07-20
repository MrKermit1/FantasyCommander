#include "world.h"
#include <random>
#include <iostream>
#include "../entities/creatures/creature.h"
#include "../player/player.h"
#include <queue>
#include <map>

World::World()
{
    map = new TerrainNode* [64];
    for (int i = 0; i < 64; i++)
    {
        map[i] = new TerrainNode[48];
    }

    camera = { 0 };
    camera.target = Vector2{ 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    GenerateWorld();
    GenerateTerrain(TerrainNode::STONE ,30);
    GenerateTerrain(TerrainNode::FOREST ,100);
}

World::World(Player* player)
{
	InitGame();
    map = new TerrainNode * [64];
    for (int i = 0; i < 64; i++)
    {
        map[i] = new TerrainNode[48];
    }

    camera = { 0 };
    camera.target = Vector2{ 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    GenerateWorld();
    GenerateTerrain(TerrainNode::STONE, 30);
    GenerateTerrain(TerrainNode::FOREST, 100);

	this->player = player;
}

std::vector<Vector2> World::FindPath(Vector2 startPos, Vector2 targetPos)
{
    struct Node
    {
        Vector2 position;
        float cost;
        float priority;
    };

	//Priority queue to store nodes based on their priority(cost + heuristic)
    auto cmp = [](Node left, Node right) { return left.priority > right.priority; };
	// Using a priority queue to implement the frontier
    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> frontier(cmp);

    std::map<std::pair<int, int>, Vector2> cameFrom;
    std::map<std::pair<int, int>, float> costSoFar;

    auto gridPos = [](Vector2 pos) { return std::make_pair((int)(pos.x / 25), (int)(pos.y / 25)); };
    auto heuristic = [](Vector2 a, Vector2 b)
    {
        return fabs(a.x - b.x) + fabs(a.y - b.y);
    };

    frontier.push({ startPos, 0, 0 });
    cameFrom[gridPos(startPos)] = startPos;
    costSoFar[gridPos(startPos)] = 0;

    while (!frontier.empty())
    {
        Node current = frontier.top();
        frontier.pop();

        if (gridPos(current.position) == gridPos(targetPos))
            break;

        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (abs(dx) + abs(dy) != 1) continue;

                int newX = (int)(current.position.x / 25) + dx;
                int newY = (int)(current.position.y / 25) + dy;

                if (newX >= 0 && newX < 64 && newY >= 0 && newY < 48)
                {
                    if (map[newX][newY].GetType() != TerrainNode::GRASS)
                        continue;

                    Vector2 nextPos = map[newX][newY].GetPosition();
                    float newCost = costSoFar[gridPos(current.position)] + 1;

                    if (!costSoFar.count(gridPos(nextPos)) || newCost < costSoFar[gridPos(nextPos)])
                    {
                        costSoFar[gridPos(nextPos)] = newCost;
                        float priority = newCost + heuristic(targetPos, nextPos);
                        frontier.push({ nextPos, newCost, priority });
                        cameFrom[gridPos(nextPos)] = current.position;
                    }
                }
            }
        }
    }

    std::vector<Vector2> path;
    Vector2 current = targetPos;
    while (gridPos(current) != gridPos(startPos))
    {
        path.push_back(current);
        if (cameFrom.find(gridPos(current)) == cameFrom.end())
        {
            path.clear();
            break;
        }
        current = cameFrom[gridPos(current)];
    }
    path.push_back(startPos);
    std::reverse(path.begin(), path.end());

    return path;
}

Camera2D* World::GetCamera()
{
    return &camera;
}

bool World::IsAnyBuildingInBuildMode()
{
    for (Building& b : playerBuildings)
    {
        std::cout << "status: " << b.IsInBuildMode() << "\n";
        if (b.IsInBuildMode())
        {
            return true;
        }
    }
   
    return false;
}

// Return 2D array with grass
void World::GenerateWorld()
{
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 48; j++)
		{
			map[i][j] = TerrainNode(Vector2{i * 25.0f, j * 25.0f}, TerrainNode::GRASS);
		}
	}
}
// Generate 2x2 terrain node on random grass node
void World::GenerateTerrain(TerrainNode::TerrainType type, int ammount)
{
    int x = RandomNumber(0, 62);
    int y = RandomNumber(0,  47);

    for (int i = 0; i < ammount; i++)
    {

        while (!(CheckTerrain(x, y, TerrainNode::GRASS)))
        {
            x = RandomNumber(0, 62);
            y = RandomNumber(0, 47);
        }

        map[x][y].SetType(type);
        map[x + 1][y].SetType(type);
        map[x][y + 1].SetType(type);
        map[x + 1][y + 1].SetType(type);
    }
}

void World::UnclickUnusedNodes(TerrainNode node)
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            if (!(map[i][j] == node))
            {
                map[i][j].UnClick();
            }
        }
    }
}

void World::WalkingOnNode(TerrainNode* node, Creature& creature, Vector2 target)
{
    Vector2 nearest = FindNearestWalkableNode(target);
    if (creature.IsClicked() && node->IsClicked())
    {
        
        std::cout << "  TYPE:" << node->GetType() << "\n";
        std::vector<Vector2> path;

        //Vector2 nearest = FindNearestWalkableNode(target);
        path = FindPath(creature.GetPosition(), nearest);
        creature.SetPath(path);
        creature.SetTargetNode(node);
        creature.SetNearestTraget(nearest);


        node->UnClick();
		
        creature.UnClick();
        if (creature.GetTargetNode()->GetType() != TerrainNode::GRASS)
        {
            creature.Take();
        }

        return;
    }
    else
    {
        if (creature.IsTaken() && !creature.IsMoving())
        {
            switch (creature.GetTargetNode()->GetType())
            {
                case TerrainNode::FOREST:
                    player->AddToWood(15);
                    creature.Take();

                    break;
                case TerrainNode::STONE:
                    player->AddToStone(15);
                    creature.Take();

                    break;
            default:
                break;
            }
        }
    }

}

void World::InitGame()
{
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 1000;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Fantasy Commander");
}

void World::AddCreature(Creature creature)
{
    playerCreatures.push_back(creature);
}

void World::AddBuilding(Building building)
{
    playerBuildings.push_back(building);
}

int World::RandomNumber(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);

    return dist6(rng);
}

bool World::CheckTerrain(int x, int y, TerrainNode::TerrainType type)
{
    return
        map[x][y].GetType() == type ||
        map[x + 1][y].GetType() == type ||
        map[x][y + 1].GetType() == type ||
        map[x + 1][y + 1].GetType() == type;
}

bool World::CheckCreatureOnPosition(Vector2 pos)
{
    for (Creature& c : playerCreatures)
    {
        if (c.GetPosition().x == pos.x && c.GetPosition().y == pos.y)
        {
            return true;
		}
    }
    
	return false;
}

bool World::CheckCreatureOnPosition(Vector2 pos, int id)
{
    for (Creature& c : playerCreatures)
    {
        if (c.GetPosition().x == pos.x && c.GetPosition().y == pos.y && c.GetId() != id)
        {
            return true;
        }
    }

    return false;
}

Vector2 World::FindNearestWalkableNode(Vector2 startPos)
{
    Vector2 bestPos = startPos;
    float bestDistance = FLT_MAX;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            int newX = (int)(startPos.x / 25) + dx;
            int newY = (int)(startPos.y / 25) + dy;

            if (newX >= 0 && newX < 64 && newY >= 0 && newY < 48)
            {
                if (map[newX][newY].GetType() == 0 && !CheckCreatureOnPosition(map[newX][newY].GetPosition()))
                {
                    float distance = sqrt(pow(startPos.x - map[newX][newY].GetPosition().x, 2) + 
                                     pow(startPos.y - map[newX][newY].GetPosition().y, 2));

                    if (distance < bestDistance)
                    {
                        bestDistance = distance;
                        bestPos = map[newX][newY].GetPosition();
                    }
                }
            }
        }
    }

    return bestPos;
}

int World::GetCreaturesQuanity()
{
    return playerCreatures.size();
}

void World::Draw()
{
    BeginMode2D(camera);
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            map[i][j].Draw();
        }
    }

    for (auto& b : playerBuildings)
    {
        b.Draw();
    }

    for (auto& c : playerCreatures)
    {
        c.Draw();
    }

    EndMode2D();
}

void World::Update()
{
    float deltaTime = GetFrameTime();

    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            currentTarget = map[i][j].OnClick(&camera);

            for (Creature& c : playerCreatures)    
            {
                WalkingOnNode(&map[i][j], c, currentTarget);
            }
        }
    }

    for (Creature& c : playerCreatures)
    {
        c.OnClick(&camera);
        c.UpdateMovement(deltaTime);
        if (c.IsMoving())
        {
            c.Animate();
        }
    }

    for (Building& b : playerBuildings)
    {
		b.Update();
    }
}

void World::Move()
{
    float speed = 10;
    if (IsKeyDown(KEY_W))
    {
        camera.target.y -= speed;
    }

    if (IsKeyDown(KEY_S))
    {
        camera.target.y += speed;
    }

    if (IsKeyDown(KEY_D))
    {
        camera.target.x += speed;
    }

    if (IsKeyDown(KEY_A))
    {
        camera.target.x -= speed;
    }

    camera.zoom += GetMouseWheelMove() * speed / 100.0f;
}
    