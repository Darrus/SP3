#ifndef STUN_STATUS_H
#define STUN_STATUS_H

#include "Status.h"
#include "Enemy.h"
#include "Particle.h"

class StunStatus : public Status
{
public:
	StunStatus();
	virtual ~StunStatus();

	virtual void Update(double dt);
	virtual void ApplyStatus(GameObject* go);
	virtual void RevertStatus();

	Enemy* enemy;
	ParticleObject* particle;
};

#endif