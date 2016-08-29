#include "Boss.h"
#include "MeshGenerator.h"

Boss::Boss()
{
	status.AddImmune("Stun");
	health = 10000;
	maxHealth = 10000;
	attackRange = 64.f;
	alertRange = 1000.f;
	patrolRange = 1000.f;
	speed = 50;
	defaultSpeed = 50;
	timeBetweenAttack = 2.f;
	attackCooldown = 0.f;
	attackDamage = 20.f;
	mesh = MeshGenerator::GetInstance().GenerateSprite("Ice Golem", "Image//IceGolem.tga", 4, 8);
	animWalk.Set(8, 11, 1.f, true, 1, true);
	animAttack.Set(16, 23, 1.f, true);
}

Boss::~Boss()
{

}

void Boss::Update(double dt)
{
	Enemy::Update(dt);
}

void Boss::Attack(Player* player)
{
	if (attackCooldown < 0)
	{
		attackCooldown = timeBetweenAttack;
		player->TakeDamage(attackDamage);

		if (pos.x > player->pos.x)
		{
			player->vel.x -= 100;
			player->vel.y += 200;
		}
		else if (pos.x < player->pos.x)
		{
			player->vel.x += 100;
			player->vel.y += 200;
		}
	}
}

void Boss::MapCollision(double dt)
{
	// Updates position
	newPos = pos + vel * (float)dt;

	// Init Variables
	int tileSize = map->GetTileSize();
	int currentX, currentY, checkUp, checkDown, checkX, checkY;
	currentX = currentY = checkDown = checkUp = checkX = checkY = 0;

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
	checkUp = (newPos.y + scale.y * 0.5f - 1) / tileSize;
	checkDown = (newPos.y - scale.y * 0.5f + 1) / tileSize;

	if (isGrounded) // If enemy is grounded
	{
		// Checks the tile below enemy
		if (map->collisionMap[checkDown - 1][checkX] != 1)
		{
			isGrounded = false;
			collidedWall = true;
		}
	}
	else if (!isGrounded) // If enemy is in the air
	{
		// Checks Down
		if (map->collisionMap[checkDown][currentX] == 1)
		{
			isGrounded = true;
			newPos.y = checkDown * tileSize + scale.y * 0.5f + tileSize;
			vel.y = 0.f;
		}
	}

	pos = newPos;
}
