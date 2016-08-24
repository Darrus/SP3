#ifndef SPRITE_PARTICLE_H
#define SPRITE_PARTICLE_H

#include "Particle.h"

class SpriteParticle : public ParticleObject
{
public:
	SpriteParticle();
	~SpriteParticle();

	virtual void Update(double dt);
};

#endif