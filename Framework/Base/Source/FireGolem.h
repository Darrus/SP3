#ifndef FIRE_GOLEM_H
#define FIRE_GOLEM_H

#include "Boss.h"

class FireGolem : public Boss
{
public:
	FireGolem();
	virtual ~FireGolem();

	virtual void Skill();
};

#endif