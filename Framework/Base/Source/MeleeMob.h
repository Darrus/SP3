#ifndef MELEE_MOB_H
#define MELEE_MOB_H

#include "Enemy.h"

class MeleeMob
{
public:
	MeleeMob();
	virtual ~MeleeMob();

	virtual void Init();
	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
};

#endif