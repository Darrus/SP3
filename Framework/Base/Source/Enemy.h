#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "TileMap.h"
#include "Player.h"
#include "StatusEffects.h"
#include "AABB_2D.h"

class EnemyStates;

class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init(TileMap* map, Vector3 pos, Vector3 scale);
	virtual void Update(double dt);
	virtual void Attack(Player* player);
	virtual void HandleInteraction(GameObject* go, double dt);
	void TakeDamage(int damage);

	void SetAttackAnim(int start, int end, float time);
	void SetWalkAnim(int start, int end, float time);
	void SetAlertRange(float range);
	void SetAttackRange(float range);
	void SetPatrolRange(float range);
	void SetAttackDamage(float damage);
	void SetTimeBetweenAttack(float time);
	void SetHealth(int health);
	void SetDefaultSpeed(float speed);
	void SetSpeed(float speed);
	void SetState(EnemyStates* state);
	void SetElement(ELEMENTS elem, int worth);

	float GetAlertRange();
	float GetAttackRange();
	float GetPatrolRange();
	float GetAttackDamage();
	float GetHealth();
	float GetMaxHealth();
	float GetDefaultSpeed();
	float GetSpeed();
	int GetWorth();
	ELEMENTS GetElement();
	EnemyStates* GetState();
	Animation GetWalkAnim();
	Animation GetAttackAnim();

	Vector3 newPos;
	bool collidedWall;
	StatusEffects status;
	AABB_2D collider;

protected:
	void MapCollision(double dt);

	Animation animWalk;
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

	ELEMENTS element;
	int captureWorth;

	TileMap* map;
	EnemyStates* state;
	bool isGrounded;
};

#endif