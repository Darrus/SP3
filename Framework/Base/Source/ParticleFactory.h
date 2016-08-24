#ifndef PARTICLE_FACTORY_H
#define PARTICLE_FACTORY_H

#include "Particle.h"
#include "GameObject.h"
#include <string>

using std::string;

class ParticleFactory
{
public:
	ParticleFactory();
	~ParticleFactory();
	
	static ParticleObject* Create(ParticleObject_TYPE type, Vector3 pos, Vector3 view);
	static ParticleObject* CreateFollow(ParticleObject_TYPE type, GameObject* go);
	static ParticleObject* CreateText(string text, float duration, Vector3 pos, Vector3 scale);
};

#endif