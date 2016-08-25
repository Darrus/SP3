#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "TileMap.h"
#include "SpriteAnimation.h"
#include "Weapon.h"
#include "NetBullet.h"
#include "AABB_2D.h"
#include "Items.h"

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

	void SetHealthRegain(int healthRegain);
	void SetPotionCount(int potionCount);

	void AddBullet(ELEMENTS elem, int amount);

	int GetWeaponType();

	ELEMENTS GetElement();
	int GetElementCount(ELEMENTS elem);

	AABB_2D collider;

private:
	void Move(double dt);
	void CycleBullets();
	void ChangeWeapon();
	void CollisionCheck(double dt);
	void PlayerJump(double dt);
	void ShootWeapon();
	void TossNet();

	void playerDeath();
	void selectSkill();
	void PlayerUseItem();
	void PlayerCycleItem();


	const float PLAYER_SPEED;
	const float JUMP_SPEED;
	const float MAX_HEIGHT;
	bool isMoving;
	bool isClimbing;
	bool isGrounded;

	TileMap* map;
	Vector3 newPos;
	
	SpriteAnimation* sprite;
	Animation idle;
	Animation run;

	PLAYER_STATE state;
	Items items;
	/*PLAYER_SKILLS skills;
	PLAYER_BULLETS bullets;*/


	int jumpHeight;
	int playerHealth;
	int playerMaxHealth;

	float mouseX, mouseY;

	Weapon* weapon[4];


	int bulletElem[ELEM_SIZE];
	ELEMENTS selectedElem;
	NetBullet* net;

	int weaponType;
	int bulletType;
};

#endif