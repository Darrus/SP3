#ifndef RANGE_ENEMY_H
#define RANGE_ENEMY_H

#include "Enemy.h"

class RangeEnemy : public Enemy
{
public:
	RangeEnemy();
	virtual ~RangeEnemy();

	virtual void Update(double dt);
	virtual void Attack(Player* player);
};

#endif