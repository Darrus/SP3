#ifndef MELEE_MOB_H
#define MELEE_MOB_H

#include "Enemy.h"

class MeleeEnemy : public Enemy
{
private:

public:
	MeleeEnemy();
	virtual ~MeleeEnemy();

	virtual void Update(double dt);
	virtual void Attack(Player* player);
};

#endif