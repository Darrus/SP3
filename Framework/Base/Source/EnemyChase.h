#ifndef ENEMY_CHASE_H
#define ENEMY_CHASE_H

#include "EnemyStates.h"

class EnemyChase : public EnemyStates
{
public:
	EnemyChase();
	virtual ~EnemyChase();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual void Update(double dt);

	float dir;
	float timer;
	float timeBetwenChecks;
};

#endif