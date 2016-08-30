#include "Player.h"
#include "Application.h"
#include "MeshGenerator.h"
#include <iostream>
#include "Pistol.h"
#include "Rifle.h"
#include "BulletFactory.h"
#include "Shotgun.h"
#include "Sniper.h"
#include "HealthPotions.h"
#include "SoundEngine.h"

Player::Player() :
PLAYER_SPEED(100),
isGrounded(false),
playerHealth(200),
playerMaxHealth(200),
JUMP_SPEED(400),
state(P_IDLE),
weaponType(0),
net(NULL)
{
	mesh = MeshGenerator::GetInstance().GenerateSprite("player", "Image//player2.tga", 3, 8);
	sprite = dynamic_cast<SpriteAnimation*>(mesh);
	idle.Set(0, 7, 2.f, active, 1, true);
	run.Set(8, 18, 1.f, active, 1, true);
	sprite->SetAnimation(idle);

	weapon[0] = new Pistol();
	weapon[0]->ReferencePlayerPos(&pos);
	weapon[0]->ReferencePlayerView(&view);

	weapon[1] = new Rifle();
	weapon[1]->ReferencePlayerPos(&pos);
	weapon[1]->ReferencePlayerView(&view);

	weapon[2] = new Shotgun();
	weapon[2]->ReferencePlayerPos(&pos);
	weapon[2]->ReferencePlayerView(&view);

	weapon[3] = new Sniper();
	weapon[3]->ReferencePlayerPos(&pos);
	weapon[3]->ReferencePlayerView(&view);

	SoundEngine::GetInstance().AddSound("Pistol", "Sound//Pistol.mp3");
	SoundEngine::GetInstance().AddSound("Rifle", "Sound//Rifle.mp3");
	SoundEngine::GetInstance().AddSound("Shotgun", "Sound//Shotgun.mp3");
	SoundEngine::GetInstance().AddSound("Sniper", "Sound//Sniper.mp3");
	SoundEngine::GetInstance().AddSound("SwitchWeapon", "Sound//SwitchWeapon.mp3");
	SoundEngine::GetInstance().AddSound("SwitchElementAndItem", "Sound//SwitchElementAndItem.mp3");
	SoundEngine::GetInstance().AddSound("Pickup", "Sound//Pickup.mp3");

	bulletElem[0] = -1;
	for (int i = 1; i < ELEM_SIZE; ++i)
	{
		bulletElem[i] = 20;
	}
	selectedElem = NONE;
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

void Player::SetPlayerMaxHealth(int playerMaxHealth)
{
	this->playerMaxHealth = playerMaxHealth;
}

int Player::GetPlayerMaxHealth(void)
{
	return playerMaxHealth;
}

void Player::AddBullet(ELEMENTS elem, int amount)
{
	bulletElem[elem] += amount;
}

float Player::getPlayerSpeed(void)
{
	return PLAYER_SPEED;
}

void Player::setPlayerSpeed(float PLAYER_SPEED)
{
	this->PLAYER_SPEED = PLAYER_SPEED;
}

void Player::Init(TileMap* map, Vector3 pos, Vector3 scale)
{
	this->map = map;
	this->pos = pos;
	this->scale = scale;
	collider.Init(&this->pos, scale);
}

void Player::Update(double dt)
{
	Move(dt);
	CollisionCheck(dt);
	CycleBullets();
	PlayerJump(dt);
	ChangeWeapon();
	ShootWeapon();
	PlayerUseItem();
	TossNet();
	PlayerCycleItem();

	collider.Update();

	for (int i = 0; i < 4; ++i)
	{
		weapon[i]->Update(dt);
	}

	view.Set(mouseX - pos.x, mouseY - pos.y, 1.f);
	view.Normalize();

	sprite->Update(dt);

}

int Player::GetWeaponType()
{
	return weaponType;
}

void Player::TakeDamage(int damage)
{
	playerHealth -= damage;
	if (playerHealth < 0)
		playerHealth = 0;

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
		if (state != P_RUN)
			sprite->SetAnimation(run);
		state = P_RUN;
	}

	if (Application::GetInstance().controller->OnHold(MOVE_LEFT))
	{
		vel.x = -PLAYER_SPEED;
		if (state != P_RUN)
			sprite->SetAnimation(run);
		state = P_RUN;
	}

	if (Application::GetInstance().controller->IsKeyReleased(MOVE_RIGHT) || Application::GetInstance().controller->IsKeyReleased(MOVE_LEFT))
	{
		vel.x = 0.f;
		if (state != P_IDLE)
			sprite->SetAnimation(idle);
		state = P_IDLE;
	}

	if (!isGrounded)
		vel.y += -9.8f;
}

void Player::ChangeWeapon()
{
	if (Application::GetInstance().controller->IsKeyPressed(TAB))
	{
		SoundEngine::GetInstance().Play("SwitchWeapon");
		weaponType++;
	}
	if (weaponType > 3)
	{
		weaponType = 0;
	}
	else if (weaponType < 0)
	{
		weaponType = 0;
	}
}

void Player::CycleBullets()
{
	if (Application::GetInstance().controller->IsKeyPressed(CYCLEBULLET))
	{
		SoundEngine::GetInstance().Play("SwitchElementAndItem");
		selectedElem = (ELEMENTS)((selectedElem + 1) % (int)ELEM_SIZE);
	}
}

void Player::PlayerCycleItem()
{
	if (Application::GetInstance().controller->IsKeyPressed(CYCLEITEM))
	{
		SoundEngine::GetInstance().Play("SwitchElementAndItem");
		inventory.CycleItems();
	}
}

void Player::PlayerUseItem()
{
	if (Application::GetInstance().controller->IsKeyPressed(USEITEM))
	{
		//items.UseItem(this);

		/*items = new HealthPotion();
		items->UseItem();
		if (playerHealth > 200)
			playerHealth = 200;*/
		inventory.UseItem();
	}
}

ELEMENTS Player::GetElement()
{
	return this->selectedElem;
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
		{
			newPos.x = pos.x;
			vel.x = 0.f;
			vel.y = 0.f;
		}
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
			newPos.y = checkDown * tileSize + scale.y * 0.5f + tileSize;
			vel.y = 0.f;
			vel.x = 0.f;
		}

		// Checks Up
		if (map->collisionMap[checkUp][checkLeft] == 1 || map->collisionMap[checkUp][checkRight] == 1)
		{
			newPos.y = checkUp * tileSize - scale.y * 0.5f;
			if (vel.y > 0.f)
				vel.y = 0.f;
		}
	}
	
	pos = newPos;
}

void Player::PlayerJump(double dt)
{
	if (Application::GetInstance().controller->IsKeyPressed(JUMP) && isGrounded)
	{
		vel.y = JUMP_SPEED;
		isGrounded = false;
	}
}

void Player::SetMousePos(float mouseX, float mouseY)
{
	this->mouseX = mouseX;
	this->mouseY = mouseY;
}

void Player::ShootWeapon()
{
	if (weapon[weaponType])
	{
		if (!weapon[weaponType]->Overheating() && Application::IsMousePressed(0) && bulletElem[selectedElem] != 0)
		{
			if (weapon[weaponType]->Shoot(selectedElem, map))
			{
				if (weaponType == 0)
					SoundEngine::GetInstance().Play("Pistol");
				if (weaponType == 1)
					SoundEngine::GetInstance().Play("Rifle");
				if (weaponType == 2)
					SoundEngine::GetInstance().Play("Shotgun");
				if (weaponType == 3)
					SoundEngine::GetInstance().Play("Sniper");
				if (bulletElem[selectedElem] > 0)
				{
					bulletElem[selectedElem] -= 1;
				}
			}
		}
	}
}

void Player::TossNet()
{
	if (net && !net->active)
		net = NULL;

	if (Application::IsMousePressed(1) && !net)
	{
		net = dynamic_cast<NetBullet*>(BulletFactory::CreateNet(pos, view, this, map));
	}
}

Weapon* Player::GetWeapon()
{
	if (weapon[weaponType])
		return weapon[weaponType];
	return NULL;
}

int Player::GetElementCount(ELEMENTS elem)
{
	return this->bulletElem[elem];
}