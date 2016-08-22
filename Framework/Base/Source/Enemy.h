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
	void TakeDamage(int damage);

	void SetAttackAnim(int start, int end, float time);
	void SetWalkLeftAnim(int start, int end, float time);
	void SetWalkRightAnim(int start, int end, float time);
	void SetAlertRange(float range);
	void SetAttackRange(float range);
	void SetPatrolRange(float range);
	void SetAttackDamage(float damage);
	void SetTimeBetweenAttack(float time);
	void SetHealth(int health);
	void SetSpeed(float speed);

	float GetAlertRange();
	float GetAttackRange();
	float GetPatrolRange();
	float GetAttackDamage();
	float GetHealth();
	float GetMaxHealth();
	float GetSpeed();
	Animation GetWalkLeftAnim();
	Animation GetWalkRightAnim();
	Animation GetAttackAnim();

	Vector3 newPos;
	bool collidedWall;
protected:
	void MapCollision(double dt);

	Animation animWalkLeft;
	Animation animWalkRight;
	Animation animAttack;

	float alertRange;
	float attackRange;
	float patrolRange;

	float speed;
	float defaultSpeed;

	float attackDamage;
	float timeBetweenAttack;
	float attackCooldown;

	int health;
	int maxHealth;

	TileMap* map;
	EnemyStates* state;
	bool isGrounded;
};

#endif