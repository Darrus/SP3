#include "Player.h"
#include "Application.h"
#include "MeshGenerator.h"
#include <iostream>
#include "Pistol.h"

Player::Player() :
PLAYER_SPEED(100),
isGrounded(false),
isMoving(false),
isClimbing(false),
playerHealth(200),
JUMP_SPEED(20),
state(P_IDLE),
MAX_HEIGHT(20),
isUsed(true)
{
	mesh = MeshGenerator::GetInstance().GenerateSprite("player", "Image//player.tga", 4, 9);
	sprite = dynamic_cast<SpriteAnimation*>(mesh);
	Animation test;
	test.Set(18, 18, 1.f, true);
	sprite->SetAnimation(test);
	weapon = new Pistol();
	weapon->ReferencePlayerPos(&pos);
	weapon->ReferencePlayerView(&view);
	bulletElem = Bullet::LIGHTNING;
}

Player::~Player()
{
}

int Player::GetPlayerHealth(void) //getters for health
{
	return playerHealth;
}

void Player::SetPlayerHealth(int playerHealth) //setters for health
{
	if (playerHealth < 0)
	{
		playerHealth = 0;
	}
	this->playerHealth = playerHealth;
}

int Player::GetHealthRegain(void)
{
	return healthRegain;
}

int Player::GetPotionCount(void)
{
	return potionCount;
}

void Player::SetHealthRegain(int healthRegain)
{
	this->healthRegain = healthRegain;
}

void Player::SetPotionCount(int potionCount)
{
	this->potionCount = potionCount;
}

void Player::Init(TileMap* map)
{
	this->map = map;
}

void Player::Update(double dt)
{
	Move(dt);
	CollisionCheck(dt);
	playerDeath();
	selectSkill();
	cycleBullets();
	playerJump(dt);
	useItem();
	changeWeapon();
	ShootWeapon();
	if (weapon)
		weapon->Update(dt);

	view.Set(mouseX - pos.x, mouseY - pos.y, 1.f);
	view.Normalize();

	//sprite->Update(dt);
}

void Player::TakeDamage(int damage)
{
	playerHealth -= damage;
}

Player::PLAYER_STATE Player::getState()
{
	return this->state;
}

void Player::Move(double dt)
{
	if (Application::GetInstance().controller->OnHold(MOVE_RIGHT))
	{
		vel.x = PLAYER_SPEED;
		state = P_WALK_RIGHT;
	}

	if (Application::GetInstance().controller->OnHold(MOVE_LEFT))
	{
		vel.x = -PLAYER_SPEED;
		state = P_WALK_LEFT;
	}

	if (Application::GetInstance().controller->IsKeyReleased(MOVE_RIGHT) || Application::GetInstance().controller->IsKeyReleased(MOVE_LEFT))
	{
		vel.x = 0.f;
	}

	if (Application::GetInstance().controller->OnHold(JUMP) && isGrounded)
	{
		vel.y = 450.f;
		isGrounded = false;
	}

	if (!isGrounded)
	{
		vel.y += -9.8f;
	}
}

void Player::playerDeath()
{
	if (playerHealth <= 0)
		state = P_DEATH;
}

void Player::selectSkill()
{
	if (Application::GetInstance().controller->IsKeyPressed(ONE))
	{
		//select skill 1
	}
	else if (Application::GetInstance().controller->IsKeyPressed(TWO))
	{
		//select skill 2
	}
	else if (Application::GetInstance().controller->IsKeyPressed(THREE))
	{
		//select skill 3
	}
}

void Player::changeWeapon()
{
	/*if (Application::GetInstance().controller->IsKeyPressed(TAB))
	{
		weaponType++;
		if (weaponType == 0)
			weapon.setWeaponType(weapon.PISTOL);

		else if (weaponType == 1)
			weapon.setWeaponType(weapon.RIFLE);
			
		else if (weaponType == 2)
			weapon.setWeaponType(weapon.SMG);

		else if (weaponType == 3)
			weapon.setWeaponType(weapon.RPG);

		else if (weaponType == 4)
			weapon.setWeaponType(weapon.SHOTGUN);

		else if (weaponType == 5)
			weapon.setWeaponType(weapon.GPMG);

		else if (weaponType == 6)
			weapon.setWeaponType(weapon.SNIPER);

		else if (weaponType >= 7)
			weaponType = 0;
		
	}*/
}

void Player::cycleBullets()
{
	if (Application::GetInstance().controller->IsKeyPressed(CYCLEBULLET))
	{
		int currentElem = bulletElem;
		currentElem = (currentElem + 1) % (int)Bullet::ELEM_SIZE;
		bulletElem = (Bullet::ELEMENT)currentElem;
		std::cout << bulletElem << std::endl;
	}
}

void Player::useItem()
{
	if (Application::GetInstance().controller->IsKeyPressed(USEITEM) && isUsed == true)
	{
		regainHealth();
	}
}

void Player::regainHealth()
{
	if (items == POTION)
	{
		if (playerHealth < 200 && isUsed == true)
		{
			playerHealth += healthRegain;
			potionCount--;
		}
		if (potionCount <= 0)
			isUsed = false;
	}
}

void Player::CollisionCheck(double dt)
{
	// Updates position
	newPos = pos + vel * (float)dt;
	
	// Init Variables
	int tileSize = map->GetTileSize();
	int currentX, currentY, checkRight, checkLeft, checkUp, checkDown, checkX, checkY;
	currentX = currentY = checkRight = checkLeft = checkDown = checkUp = checkX = checkY = 0;

	// Make sure object doesnt move out of screen
	if (newPos.x - scale.x * 0.5f <= 0 || newPos.x + scale.x * 0.5f >= map->GetMapWidth())
		newPos.x = pos.x;
	if (newPos.y - scale.y * 0.5f <= 0 || newPos.y + scale.y * 0.5f >= map->GetMapHeight())
		newPos.y = pos.y;
	
	// Get Current Tile
	currentX = (int)newPos.x / tileSize;
	currentY = (int)newPos.y / tileSize;

	// Check which direction is the player moving in the X axis
	float dir = 0;
	dir = newPos.x - pos.x;
	
	// Checks next tile according to player's scale
	checkRight = (int)((newPos.x + scale.x * 0.5f) / tileSize);
	checkLeft = (int)((newPos.x - scale.x * 0.5f) / tileSize);
	checkUp = (int)((newPos.y + scale.y * 0.5f) / tileSize);
	checkDown = (int)((newPos.y - scale.y * 0.5f) / tileSize);

	if (dir > 0)
		checkX = checkRight;
	else
		checkX = checkLeft;
		

	if (isGrounded) // If enemy is grounded
	{
		// Checks the tile below enemy
		if (map->collisionMap[currentY - 1][checkRight] != 1 && map->collisionMap[currentY - 1][checkLeft] != 1 && map->collisionMap[currentY - 1][currentX] != 1)
			isGrounded = false;

		// Check the next tile
		if (map->collisionMap[currentY][checkX] == 1)
			newPos.x = pos.x;
	}
	else if (!isGrounded) // If enemy is in the air
	{
		// Checks X
		if (map->collisionMap[checkUp][checkX] == 1 || map->collisionMap[checkDown][checkX] == 1)
		{
			newPos.x = pos.x;
			checkRight = (int)((newPos.x + scale.x * 0.5f) / tileSize);
			checkLeft = (int)((newPos.x - scale.x * 0.5f) / tileSize);
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

void Player::playerJump(double dt)
{
	if (Application::GetInstance().controller->IsKeyPressed(JUMP) && isGrounded == true)
		pos.y += JUMP_SPEED * (float)dt;
}

void Player::SetMousePos(float mouseX, float mouseY)
{
	this->mouseX = mouseX;
	this->mouseY = mouseY;
}

void Player::ShootWeapon()
{
	if (weapon)
		if (!weapon->Overheating() && Application::IsMousePressed(0))
				weapon->Shoot(bulletElem, map);
}

Weapon* Player::GetWeapon()
{
	if (weapon)
		return weapon;
	return NULL;
}