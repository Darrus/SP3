#ifndef ENEMY_STATES_H
#define ENEMY_STATES_H

#include "Player.h"
#include "Enemy.h"

class EnemyStates
{
public:
	EnemyStates();
	virtual ~EnemyStates();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual EnemyStates* CheckState();
	virtual void Update(double dt);

	Enemy* enemy;
	Player* player;
};

#endif