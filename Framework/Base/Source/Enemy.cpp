#include "Enemy.h"
#include "Player.h"
#include "EnemyIdle.h"

Enemy::Enemy() :
collidedWall(false),
alertRange(0.f),
attackRange(0.f),
patrolRange(0.f),
speed(0.f),
defaultSpeed(0.f),
attackDamage(0.f),
timeBetweenAttack(0.f),
attackCooldown(0.f),
health(0),
maxHealth(0),
map(NULL),
state(NULL)
{
	status.SetObject(this);
}

Enemy::~Enemy()
{
	
}

void Enemy::Init(TileMap* map)
{
	this->map = map;
}

void Enemy::Update(double dt)
{
	status.Update(dt);

	attackCooldown -= dt;

	if (state)
		state->Update(dt);

	collidedWall = false;

	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(mesh);
	if (sprite)
		sprite->Update(dt);

	if (!isGrounded)
		vel.y -= 9.8;

	MapCollision(dt);

	if (health <= 0 && active)
		active = false;

}

void Enemy::HandleInteraction(GameObject* go, double dt)
{
	
}

void Enemy::TakeDamage(int damage)
{
	this->health -= damage;
}

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

void Enemy::Attack(Player* player)
{

}

void Enemy::SetAttackAnim(int start, int end, float time)
{
	animAttack.Set(start, end, time, true, 1);
}

void Enemy::SetWalkLeftAnim(int start, int end, float time)
{
	animWalkLeft.Set(start, end, time, true, 1, true);
}

void Enemy::SetWalkRightAnim(int start, int end, float time)
{
	animWalkRight.Set(start, end, time, 1, true);
}

void Enemy::SetAlertRange(float range)
{
	alertRange = range;
}

void Enemy::SetAttackRange(float range)
{
	attackRange = range;
}

void Enemy::SetPatrolRange(float range)
{
	patrolRange = range;
}

void Enemy::SetAttackDamage(float damage)
{
	attackDamage = damage;
}

void Enemy::SetTimeBetweenAttack(float time)
{
	timeBetweenAttack = time;
}

void Enemy::SetHealth(int health)
{
	maxHealth = health;
	this->health = health;
}

void Enemy::SetDefaultSpeed(float speed)
{
	this->speed = speed;
	defaultSpeed = speed;
}

void Enemy::SetSpeed(float speed)
{
	this->speed = speed;
}

void Enemy::SetState(EnemyStates* state)
{
	if (this->state)
		delete this->state;

	this->state = state;
}

void Enemy::SetElement(ELEMENTS elem, int worth)
{
	element = elem;
	captureWorth = worth;
}

float Enemy::GetDefaultSpeed()
{
	return defaultSpeed;
}

float Enemy::GetAlertRange()
{
	return alertRange;
}

float Enemy::GetAttackRange()
{
	return attackRange;
}

float Enemy::GetPatrolRange()
{
	return patrolRange;
}

float Enemy::GetAttackDamage()
{
	return attackDamage;
}

float Enemy::GetHealth()
{
	return health;
}

float Enemy::GetMaxHealth()
{
	return maxHealth;
}

float Enemy::GetSpeed()
{
	return speed;
}

ELEMENTS Enemy::GetElement()
{
	return element;
}

int Enemy::GetWorth()
{
	return captureWorth;
}

EnemyStates* Enemy::GetState()
{
	return state;
}

Animation Enemy::GetWalkLeftAnim()
{
	return animWalkLeft;
}

Animation Enemy::GetWalkRightAnim()
{
	return animWalkRight;
}

Animation Enemy::GetAttackAnim()
{
	return animAttack;
}
