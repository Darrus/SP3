#ifndef TEXT_PARTICLE_H
#define TEXT_PARTICLE_H

#include <string>
#include "Particle.h"

using std::string;

class TextParticle : public ParticleObject
{
public:
	TextParticle();
	virtual ~TextParticle();
	virtual void Update(double dt);
	string text;
	float duration;
};

#endif