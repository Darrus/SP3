#ifndef ENEMY_DEATH_H
#define ENEMY_DEATH_H

#include "EnemyStates.h"

class EnemyDeath : public EnemyStates
{
public:
	EnemyDeath();
	virtual ~EnemyDeath();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual void Update(double dt);
};

#endif