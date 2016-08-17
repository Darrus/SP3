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
	int GetPlayerHealth(void);
	void SetPlayerHealth(int playerHealth);
	SpriteAnimation* GetMesh();

private:
	void Move(double dt);
	void Jump(double dt);
	void CollisionCheck(double dt);
	void playerDeath();
	void selectSkill();
	void cycleBullets();
	void useItem();
	void changeWeapon();

	int GetHealthRegain(void);
	int GetPotionCount(void);

	void SetHealthRegain(int healthRegain);
	void SetPotionCount(int potionCount);

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

	//Jump stuff
	bool isJumping;
	bool isFalling;
	bool jumping(void);
	bool falling(void);
	bool grounded(void);

	void playerJump(double dt);

	int jumpHeight;

	int playerHealth;

	int healthRegain;
	int potionCount;

	Weapon weapon;
	Bullet bullet;

	bool isUsed;
	int weaponType;
	int bulletType;
};

#endif