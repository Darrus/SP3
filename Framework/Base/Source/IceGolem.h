#ifndef ICE_GOLEM_H
#define ICE_GOLEM_H

#include "Boss.h"

class IceGolem : public Boss
{
public:
	IceGolem();
	virtual ~IceGolem();

	virtual void Skill();
};

#endif