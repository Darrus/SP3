#ifndef EARTH_GOLEM_H
#define EARTH_GOLEM_H

#include "Boss.h"

class EarthGolem : public Boss
{
public:
	EarthGolem();
	virtual ~EarthGolem();

	virtual void Skill();
};

#endif