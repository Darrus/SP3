#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "TileMap.h"
#include "Player.h"

class EnemyStates;

class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init(TileMap* map);
	virtual void Update(double dt);
	virtual void Attack(Player* player);
	virtual void HandleInteraction(GameObject* go, double dt);


	void SetAttackAnimation(int start, int end, float time);

	Vector3 newPos;

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

	int health;
	int maxHealth;

protected:
	void MapCollision(double dt);

	TileMap* map;
	EnemyStates* state;
	bool isGrounded;
};

#endif