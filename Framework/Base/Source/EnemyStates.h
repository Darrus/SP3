#ifndef ENEMY_STATES_H
#define ENEMY_STATES_H

#include "Player.h"
#include "Enemy.h"

class EnemyStates
{
public:
	enum ENEMY_STATES
	{
		ENEMY_IDLE,
		ENEMY_CHASE,
		ENEMY_ATTACK,
		ENEMY_STUN,
		ENEMY_SKILL,
		ENEMY_DEATH
	};

	EnemyStates();
	virtual ~EnemyStates();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual void Update(double dt);
	ENEMY_STATES GetState();

	Enemy* enemy;
	Player* player;
	ENEMY_STATES state;
};

#endif