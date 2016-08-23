#ifndef RANGE_ENEMY_H
#define RANGE_ENEMY_H

#include "Enemy.h"

class RangeEnemy : public Enemy
{
public:
	RangeEnemy();
	virtual ~RangeEnemy();

	virtual void Init(TileMap* map);
	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
	virtual void Attack(Player* player);
};

#endif