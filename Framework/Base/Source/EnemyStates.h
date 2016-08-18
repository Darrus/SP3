#ifndef ENEMY_STATES_H
#define ENEMY_STATES_H

#include "Player.h"
#include "Enemy.h"

class EnemyStates
{
public:
	EnemyStates();
	virtual ~EnemyStates();

	virtual void Enter(Enemy& enemy, Player& player);
	virtual EnemyStates* CheckState(Enemy& enemy, Player& player);
	virtual void Exit();
	virtual void Update(double dt);
};

#endif