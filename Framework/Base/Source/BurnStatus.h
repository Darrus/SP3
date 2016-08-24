#ifndef BURN_STATUS_H
#define BURN_STATUS_H

#include "Status.h"
#include "Enemy.h"
#include "SpriteParticle.h"

class BurnStatus : public Status
{
public:
	BurnStatus();
	~BurnStatus();

	virtual void Update(double dt);
	virtual void ApplyStatus(GameObject* go);

	Enemy* enemy;
	int damage;
	float timeBetweenBurn;

	ParticleObject* particle;
};

#endif