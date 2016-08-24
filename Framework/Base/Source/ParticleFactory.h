#ifndef PARTICLE_FACTORY_H
#define PARTICLE_FACTORY_H

#include "Particle.h"
#include "GameObject.h"
#include <string>

using std::string;

enum PARTICLES_TYPE
{
	P_LIGHTNING,
};

class ParticleFactory
{
public:
	ParticleFactory();
	~ParticleFactory();
	
	static ParticleObject* Create(PARTICLES_TYPE type, Vector3 pos, Vector3 view, GameObject* go = NULL);
	static ParticleObject* CreateText(string text, float duration, Vector3 pos, Vector3 scale);
};

#endif