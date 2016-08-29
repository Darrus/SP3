#ifndef ENEMY_ATTACK_H
#define ENEMY_ATTACK_H

#include "EnemyStates.h"

class EnemyAttack : public EnemyStates
{
public:
	EnemyAttack();
	virtual ~EnemyAttack();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual void Update(double dt);
};

#endif