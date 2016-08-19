#ifndef ENEMY_ATTACK_H
#define ENEMY_ATTACK_H

#include "EnemyStates.h"

class EnemyAttack : public EnemyStates
{
public:
	EnemyAttack();
	virtual ~EnemyAttack();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual EnemyStates* CheckState();
	virtual void Update(double dt);
};

#endif