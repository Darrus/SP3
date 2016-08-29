#ifndef ENEMY_SKILL_H
#define ENEMY_SKILL_H

#include "EnemyStates.h"

class EnemySkill : public EnemyStates
{
public:
	EnemySkill();
	virtual ~EnemySkill();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual void Update(double dt);
};

#endif