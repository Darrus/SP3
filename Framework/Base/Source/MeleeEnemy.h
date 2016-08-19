#ifndef MELEE_MOB_H
#define MELEE_MOB_H

#include "EnemyStates.h"

class MeleeEnemy : public Enemy
{
private:

public:
	MeleeEnemy();
	virtual ~MeleeEnemy();

	virtual void Init(TileMap* map);
	virtual void Update(double dt);
	virtual void Attack(Player* player);
	virtual void HandleInteraction(GameObject* go, double dt);

	EnemyStates* state;
};

#endif