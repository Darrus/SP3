#ifndef SLOW_STATUS_H
#define SLOW_STATUS_H

#include "Status.h"
#include "Enemy.h"
#include "Particle.h"

class SlowStatus : public Status
{
public:
	SlowStatus();
	virtual ~SlowStatus();

	virtual void Update(double dt);
	virtual void ApplyStatus(GameObject* go);
	virtual void RevertStatus();

	Enemy* enemy;
	ParticleObject* particle;
};

#endif