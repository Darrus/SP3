#include "Enemy.h"


Enemy::Enemy() :
sprite(NULL)
{
}

Enemy::~Enemy()
{
	
}

void Enemy::Init(TileMap* map)
{

}

void Enemy::Update(double dt)
{

}

void Enemy::SetAttackAnimation(int start, int end, float time)
{
	animAttack.Set(start, end, time, false);
}

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}

void Enemy::MapCollision(double dt)
{
	// Updates position
	newPos = pos + vel * (float)dt;

	// Init Variables
	int tileSize = map->GetTileSize();
	int currentX, currentY, checkX, checkY;
	currentX = currentY = checkX = checkY = 0;

	// Make sure object doesnt move out of screen
	if (newPos.x - scale.x * 0.5f <= 0 || newPos.x + scale.x * 0.5f >= map->GetMapWidth())
		newPos.x = pos.x;
	if (newPos.y - scale.y * 0.5f <= 0 || newPos.y + scale.y * 0.5f >= map->GetMapHeight())
		newPos.y = pos.y;

	// Get Current Tile
	currentX = (int)newPos.x / tileSize;
	currentY = (int)newPos.y / tileSize;

	// Check which direction is the player moving in the X axis
	short dir = 0;
	dir = newPos.x - pos.x;

	// Checks next tile according to player's scale
	if (dir > 0)
		checkX = (newPos.x + scale.x * 0.5f) / tileSize;
	else
		checkX = (newPos.x - scale.x * 0.5f) / tileSize;


	if (isGrounded) // If player is grounded
	{
		// Checks the tile below player
		if (map->collisionMap[currentY - 1][currentX] != 1)
			isGrounded = false;

		// Check the next tile
		if (map->collisionMap[currentY][checkX] == 1)
			newPos.x = pos.x;
	}
	else if (!isGrounded) // If player is in the air
	{
		// Checks which direction is the player moving in the Y axis
		dir = newPos.y - pos.y;
		if (dir > 0)
			checkY = (newPos.y + scale.y * 0.5f) / tileSize;
		else
			checkY = (newPos.y - scale.y * 0.5f) / tileSize;

		// Checks Y axis
		if (map->collisionMap[checkY][currentX] == 1)
		{
			if (dir <= 0)
				isGrounded = true;
			newPos.y = (currentY * tileSize) + tileSize * 0.5f;
			vel.y = 0.f;
		}

		// Check X axis
		if (map->collisionMap[checkY][checkX] == 1 || map->collisionMap[currentY][checkX] == 1)
			newPos.x = pos.x;
	}

	pos = newPos;
}