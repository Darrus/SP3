#ifndef ENEMY_IDLE_H
#define ENEMY_IDLE_H

#include "EnemyStates.h"
#include "Vector3.h"

class EnemyIdle : public EnemyStates
{
public:
	EnemyIdle();
	virtual ~EnemyIdle();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual EnemyStates* CheckState();
	virtual void Update(double dt);

	float patrolDistance;
	int dir;
	Enemy* enemy;
};

#endif