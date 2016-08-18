#ifndef RANGE_ENEMY_H
#define RANGE_ENEMY_H

#include "GameObject.h"

class RangeEnemy
{
public:
	RangeEnemy();
	virtual ~RangeEnemy();

	virtual void Init();
	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
};

#endif