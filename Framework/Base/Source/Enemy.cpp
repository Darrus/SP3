#include "Enemy.h"
#include "Player.h"
#include "EnemyIdle.h"

Enemy::Enemy() :
sprite(NULL),
collidedWall(false)
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

void Enemy::Attack()
{

}

/*void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}*/

void Enemy::MapCollision(double dt)
{
	// Updates position
	newPos = pos + vel * (float)dt;

	// Init Variables
	int tileSize = map->GetTileSize();
	int currentX, currentY, checkRight, checkLeft, checkUp, checkDown, checkX, checkY;
	currentX = currentY = checkRight = checkLeft = checkDown = checkUp = checkX = checkY = 0;

	// Make sure object doesnt move out of screen
	if (newPos.x - scale.x * 0.5f <= 0 || newPos.x + scale.x * 0.5f >= map->GetMapWidth())
	{
		collidedWall = true;
		newPos.x = pos.x;
	}

	if (newPos.y - scale.y * 0.5f <= 0 || newPos.y + scale.y * 0.5f >= map->GetMapHeight())
		newPos.y = pos.y;

	// Get Current Tile
	currentX = newPos.x / tileSize;
	currentY = newPos.y / tileSize;

	// Check which direction is the player moving in the X axis
	float dir = 0;
	dir = newPos.x - pos.x;

	// Checks next tile according to player's scale
	checkRight = (newPos.x + scale.x * 0.5f) / tileSize;
	checkLeft = (newPos.x - scale.x * 0.5f) / tileSize;
	checkUp = (newPos.y + scale.y * 0.5f) / tileSize;
	checkDown = (newPos.y - scale.y * 0.5f) / tileSize;

	if (dir > 0)
		checkX = checkRight;
	else
		checkX = checkLeft;


	if (isGrounded) // If enemy is grounded
	{
		// Checks the tile below enemy
		if (map->collisionMap[currentY - 1][checkRight] != 1 && map->collisionMap[currentY - 1][checkLeft] != 1)
			isGrounded = false;

		// Check the next tile
		if (map->collisionMap[currentY][checkX] == 1)
		{
			newPos.x = pos.x;
			collidedWall = true;
		}
	}
	else if (!isGrounded) // If enemy is in the air
	{
		// Checks X
		if (map->collisionMap[checkUp][checkX] == 1 || map->collisionMap[checkDown][checkX] == 1)
		{
			newPos.x = pos.x;
			checkRight = (newPos.x + scale.x * 0.5f) / tileSize;
			checkLeft = (newPos.x - scale.x * 0.5f) / tileSize;
		}

		// Checks Down
		if (map->collisionMap[checkDown][checkLeft] == 1 || map->collisionMap[checkDown][checkRight] == 1)
		{
			isGrounded = true;
			newPos.y = (currentY * tileSize) + tileSize * 0.5f;
			vel.y = 0.f;
		}

		// Checks Up
		if (map->collisionMap[checkUp][checkLeft] == 1 || map->collisionMap[checkUp][checkRight] == 1)
		{
			newPos.y = checkUp * tileSize - tileSize * 0.5f;
			if (vel.y > 0.f)
				vel.y = 0.f;
		}
	}

	pos = newPos;
}

void Enemy::HandleInteraction(GameObject* go, double dt)
{
	
}
