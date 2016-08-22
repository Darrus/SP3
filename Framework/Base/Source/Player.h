#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "TileMap.h"
#include "SpriteAnimation.h"
#include "Weapon.h"

class Player : public GameObject
{
	enum PLAYER_STATE
	{
		P_IDLE,
		P_WALK_RIGHT,
		P_WALK_LEFT,
		P_CLIMB,
		P_JUMP,
		P_DEATH,
	};

	enum ITEMLIST
	{
		POTION,
	};


public:
	Player();
	~Player();

	virtual void Init(TileMap* map);
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

	void SetHealthRegain(int healthRegain);
	void SetPotionCount(int potionCount);

	int GetWeaponType();

private:
	void Move(double dt);
	void Jump(double dt);
	void CollisionCheck(double dt);
	void playerDeath();
	void selectSkill();
	void cycleBullets();
	void useItem();
	void changeWeapon();
	void playerJump(double dt);

	void ShootWeapon();
	void regainHealth();

	const float PLAYER_SPEED;
	const float JUMP_SPEED;
	const float MAX_HEIGHT;
	bool isMoving;
	bool isClimbing;
	bool isGrounded;

	TileMap* map;
	Vector3 newPos;
	
	SpriteAnimation* sprite;

	PLAYER_STATE state;
	ITEMLIST items;
	/*PLAYER_SKILLS skills;
	PLAYER_BULLETS bullets;*/


	int jumpHeight;
	int playerHealth;
	int healthRegain;
	int potionCount;

	float mouseX, mouseY;

	Weapon* weapon[2];
	Bullet::ELEMENT bulletElem;

	bool isUsed;
	int weaponType;
	int bulletType;
};

#endif