#include "Player.h"
#include "Application.h"
#include "MeshGenerator.h"

#include <iostream>

Player::Player() :
PLAYER_SPEED(100),
isGrounded(false),
isMoving(false),
isClimbing(false),
state(P_IDLE),
mesh(nullptr)
{
	mesh = MeshGenerator::GenerateSprite("player", "Image//player.tga", 4, 9);	
}

Player::~Player()
{
	if (mesh)
		delete mesh;
}

void Player::Init(TileMap* map)
{
	this->map = map;
}

void Player::Update(double dt)
{
	Move(dt);
	if (!isGrounded && !isClimbing)
	{
		vel.y += -9.8f;
	}
	CollisionCheck(dt);
}

void Player::Move(double dt)
{
	if (Application::GetInstance().controller->IsKeyPressed(MOVE_RIGHT))
	{
		pos.x += PLAYER_SPEED * dt;
	}

	if (Application::GetInstance().controller->IsKeyPressed(MOVE_LEFT))
	{
		pos.x -= PLAYER_SPEED * dt;

	}

	if (Application::GetInstance().controller->IsKeyPressed(MOVE_UP))
	{
		pos.y += PLAYER_SPEED * dt;

	}

	if (Application::GetInstance().controller->IsKeyPressed(MOVE_DOWN))
	{
		pos.y -= PLAYER_SPEED * dt;
	}
}

void Player::CollisionCheck(double dt)
{
	/*newPos = pos + vel * (float)dt;

	int currentX, currentY;
	currentX = newPos.x / map->GetTileSize();
	currentY = map->getNumOfTiles_MapHeight() - newPos.y / map->GetTileSize();

	int checkDir = newPos.x - pos.x;
	int checkX = 0, checkY = 0;
	float halfX = scale.x * 0.5f;
	float halfY = scale.y * 0.5f;
	int checkUpY = map->getNumOfTiles_MapHeight() - ((newPos.y + halfY) / map->GetTileSize());

	if (checkDir > 0)
		checkX = (newPos.x + halfX) / map->GetTileSize();
	else if (checkDir < 0)
		checkX = (newPos.x - halfX) / map->GetTileSize();

	checkY = map->getNumOfTiles_MapHeight() - ((newPos.y - halfY) / map->GetTileSize());

	if (isGrounded)
	{
		if (map->theCollisionMap[checkY][currentX] == 1)
			newPos.y = pos.y;
		else
			isGrounded = false;

		if (newPos.x - halfX <= 0 || newPos.x + halfX >= map->GetMapWidth()
			|| map->theCollisionMap[currentY][checkX] == 1)
			newPos.x = pos.x;
	}
	else if (isClimbing)
	{
		vel.y = 0.f;
		if (map->theCollisionMap[checkY][currentX] == 1)
		{
			isGrounded = true;
			isClimbing = false;
			newPos.y = ((map->getNumOfTiles_MapHeight() - checkY) * map->GetTileSize()) + halfY;
		}
		else if (map->theCollisionMap[checkY][currentX] == 0)
		{
			isGrounded = false;
			isClimbing = false;
		}

		if (newPos.x - halfX <= 0 || newPos.x + halfX >= map->GetMapWidth()
			|| map->theCollisionMap[currentY][checkX] == 1)
			newPos.x = pos.x;

	}
	else
	{
		if (map->theCollisionMap[checkY][currentX] == 1)
		{
			newPos.y = ((map->getNumOfTiles_MapHeight() - checkY) * map->GetTileSize()) + halfY;
			isGrounded = true;
			vel.y = 0.f;
		}
		else if (map->theCollisionMap[checkUpY][currentX] == 1)
		{
			vel.y = 0.f;
			newPos.y = (map->getNumOfTiles_MapHeight() - (currentY)) * map->GetTileSize() - halfY;
		}

		if (newPos.x - halfX <= 0 || newPos.x + halfX >= map->GetMapWidth() ||
			map->theCollisionMap[currentY][checkX] == 1 || map->theCollisionMap[checkY][checkX] == 1 ||
			map->theCollisionMap[checkUpY][checkX] == 1)
			newPos.x = pos.x;
	}
	
	pos = newPos;*/
}

SpriteAnimation* Player::GetMesh()
{
	return mesh;
}
