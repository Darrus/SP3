#ifndef LIGHTNING_PARTICLE_H
#define LIGHTNING_PARTICLE_H

#include "Particle.h"

class LightningParticle : public ParticleObject
{
public:
	LightningParticle();
	virtual ~LightningParticle();

	virtual void Update(double dt);
};

#endif