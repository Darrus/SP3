#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "TileMap.h"
#include "SpriteAnimation.h"
#include "Weapon.h"
#include "NetBullet.h"
#include "AABB_2D.h"
#include "Items.h"
#include "ItemList.h"

class Player : public GameObject
{
	enum PLAYER_STATE
	{
		P_IDLE,
		P_RUN,
		P_CLIMB,
		P_JUMP,
		P_DEATH,
	};



public:
	Player();
	~Player();

	virtual void Init(TileMap* map, Vector3 pos, Vector3 scale);
	virtual void Update(double dt);
	void TakeDamage(int damage);
	
	void SetPlayerHealth(int playerHealth);
	void SetMousePos(float mouseX, float mouseY);

	int GetPlayerHealth(void);
	Weapon* GetWeapon();

	SpriteAnimation* GetMesh();
	PLAYER_STATE getState();

	int GetHealthRegain(void);
	int GetPotionCount(void);
	void SetPlayerMaxHealth(int playerMaxHealth);
	int GetPlayerMaxHealth(void);

	float getPlayerSpeed(void);
	void setPlayerSpeed(float PLAYER_SPEED);

	void SetHealthRegain(int healthRegain);
	void SetPotionCount(int potionCount);

	int getCoinAmount(void);
	void SetCoinAmount(int coinAmount);

	void AddBullet(ELEMENTS elem, int amount);
	void AddCoints();

	int GetWeaponType();

	ELEMENTS GetElement();
	int GetElementCount(ELEMENTS elem);

	AABB_2D collider;
	ItemList inventory;

private:
	void Move(double dt);
	void CycleBullets();
	void ChangeWeapon();
	void CollisionCheck(double dt);
	void PlayerJump(double dt);
	void ShootWeapon();
	void TossNet();

	void PlayerUseItem();
	void PlayerCycleItem();

	float PLAYER_SPEED;
	float JUMP_SPEED;

	bool isGrounded;

	TileMap* map;
	Vector3 newPos;
	
	SpriteAnimation* sprite;
	Animation idle;
	Animation run;

	PLAYER_STATE state;

	int jumpHeight;
	int playerHealth;
	int playerMaxHealth;

	float mouseX, mouseY;
	float timer;

	Weapon* weapon[4];

	int bulletElem[ELEM_SIZE];
	ELEMENTS selectedElem;
	NetBullet* net;

	int weaponType;
	int bulletType;

	int coinAmount;
};

#endif