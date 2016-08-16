#include "Player.h"
#include "Application.h"
#include "MeshGenerator.h"

#include <iostream>

Player::Player() :
PLAYER_SPEED(100),
isGrounded(false),
isMoving(false),
isClimbing(false),
playerHealth(200),
JUMP_SPEED(20),
state(P_IDLE),
MAX_HEIGHT(20),
isUsed(true),
//skills(P_SKILL1),
//bullets(P_TYPE1),
mesh(nullptr)
{
	mesh = MeshGenerator::GenerateSprite("player", "Image//player.tga", 4, 9);	
}

Player::~Player()
{
	if (mesh)
		delete mesh;
}

int Player::GetPlayerHealth(void) //getters for health
{
	return playerHealth;
}

void Player::SetPlayerHealth(int playerHealth) //setters for health
{
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
	if (!isGrounded && !isClimbing)
	{
		vel.y += -9.8f;
	}
	CollisionCheck(dt);
	playerDeath();
	selectSkill();
	cycleBullets();
	playerJump(dt);
	useItem();
	changeWeapon();
}

void Player::Move(double dt)
{
	if (Application::GetInstance().controller->IsKeyPressed(MOVE_RIGHT) && isClimbing == true)
	{
		pos.x += PLAYER_SPEED * dt * 0.5;
	}

	if (Application::GetInstance().controller->IsKeyPressed(MOVE_LEFT))
	{
		pos.x -= PLAYER_SPEED * (float)dt;

	}

	if (Application::GetInstance().controller->IsKeyPressed(MOVE_UP))
	{
		pos.y += PLAYER_SPEED * (float)dt;

	}

	if (Application::GetInstance().controller->IsKeyPressed(MOVE_DOWN) && isClimbing == true)
	{
		pos.y -= PLAYER_SPEED * (float)dt;
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
	if (Application::GetInstance().controller->IsKeyPressed(TAB))
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
		
	}
}



void Player::cycleBullets()
{
	if (Application::GetInstance().controller->IsKeyPressed(CYCLEBULLET))
	{
		bulletType++;
		if (bulletType == 0)
			bullet.setBulletElement(bullet.FIRE);

		else if (bulletType == 1)
			bullet.setBulletElement(bullet.LIGHTNING);

		else if (bulletType == 2)
			bullet.setBulletElement(bullet.ICE);

		else if (bulletType >= 3)
			bulletType = 0;
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
	newPos = pos + vel * (float)dt;

	int currentX, currentY;
	currentX = newPos.x / map->GetTileSize();
	currentY = map->GetNumOfTiles_MapHeight() - newPos.y / map->GetTileSize();

	int checkDir = newPos.x - pos.x;
	int checkX = 0, checkY = 0;
	float halfX = scale.x * 0.5f;
	float halfY = scale.y * 0.5f;
	int checkUpY = map->GetNumOfTiles_MapHeight() - ((newPos.y + halfY) / map->GetTileSize());

	if (checkDir > 0)
		checkX = (newPos.x + halfX) / map->GetTileSize();
	else if (checkDir < 0)
		checkX = (newPos.x - halfX) / map->GetTileSize();

	checkY = map->GetNumOfTiles_MapHeight() - ((newPos.y - halfY) / map->GetTileSize());

	if (isGrounded)
	{
		if (map->collisionMap[checkY][currentX] == 1)
			newPos.y = pos.y;
		else
			isGrounded = false;

		if (newPos.x - halfX <= 0 || newPos.x + halfX >= map->GetMapWidth()
			|| map->collisionMap[currentY][checkX] == 1)
			newPos.x = pos.x;
	}
	else if (isClimbing)
	{
		vel.y = 0.f;
		if (map->collisionMap[checkY][currentX] == 1)
		{
			isGrounded = true;
			isClimbing = false;
			newPos.y = ((map->GetNumOfTiles_MapHeight() - checkY) * map->GetTileSize()) + halfY;
		}
		else if (map->collisionMap[checkY][currentX] == 0)
		{
			isGrounded = false;
			isClimbing = false;
		}

		if (newPos.x - halfX <= 0 || newPos.x + halfX >= map->GetMapWidth()
			|| map->collisionMap[currentY][checkX] == 1)
			newPos.x = pos.x;

	}
	else
	{
		if (map->collisionMap[checkY][currentX] == 1)
		{
			newPos.y = ((map->GetNumOfTiles_MapHeight() - checkY) * map->GetTileSize()) + halfY;
			isGrounded = true;
			vel.y = 0.f;
		}
		else if (map->collisionMap[checkUpY][currentX] == 1)
		{
			vel.y = 0.f;
			newPos.y = (map->GetNumOfTiles_MapHeight() - (currentY)) * map->GetTileSize() - halfY;
		}

		if (newPos.x - halfX <= 0 || newPos.x + halfX >= map->GetMapWidth() ||
			map->collisionMap[currentY][checkX] == 1 || map->collisionMap[checkY][checkX] == 1 ||
			map->collisionMap[checkUpY][checkX] == 1)
			newPos.x = pos.x;
	}
	
	pos = newPos;
}

//Jump stuff
bool Player::grounded(void)
{
	if (isJumping == false && isFalling == false)
		return true;

	return false;
}

bool Player::jumping(void)
{
	if (isGrounded == false && isFalling == false)
		return true;

	return false;
}

bool Player::falling(void)
{
	if (isGrounded == false && isJumping == false)
		return true;

	return false;
}

void Player::playerJump(double dt)
{
	if (Application::GetInstance().controller->IsKeyPressed(JUMP) && isGrounded == true)
	{
		if (isJumping == false && isFalling == false)
		{
			pos.y += JUMP_SPEED * dt;
		}
	}
	if (pos.y == MAX_HEIGHT)
	{
		isJumping = false;
		isFalling = true;
	}
	if (isFalling == true)
	{
		pos.y -= JUMP_SPEED * (float)dt;
	}

}



SpriteAnimation* Player::GetMesh()
{
	return mesh;
}
