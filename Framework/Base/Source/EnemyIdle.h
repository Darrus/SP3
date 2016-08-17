#ifndef ENEMY_IDLE_H
#define ENEMY_IDLE_H

#include "EnemyStates.h"

class EnemyIdle : public EnemyStates
{
public:
	EnemyIdle();
	virtual ~EnemyIdle();

	virtual void Enter(Enemy& enemy, Player& player);
	virtual EnemyStates* CheckState(Enemy& enemy, Player& player);
	virtual void Update(double dt);
};

#endif