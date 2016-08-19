#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "SpriteAnimation.h"
#include "Player.h"
#include "TileMap.h"

class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init(TileMap* map);
	virtual void Update(double dt);
	//virtual void HandleInteraction(GameObject* go, double dt);

	void SetAttackAnimation(int start, int end, float time);
	void SetPlayer(Player* player);

	Vector3 newPos;

	SpriteAnimation* sprite;
	Animation animWalkLeft;
	Animation animWalkRight;
	Animation animAttack;

	bool collidedWall;
	float AlertRange;
	float AttackRange;
	float PatrolRange;

	float EnemySpeed;
	float MaxSpeed;

	float AttackDamage;
	float TimeBetweenAttack;
	float AttackCooldown;
protected:
	void MapCollision(double dt);

	TileMap* map;
	Player* player;
	bool isGrounded;
};

#endif