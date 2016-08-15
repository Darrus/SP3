#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3.h"

enum ParticleObject_TYPE
{
	P_SNOWFLAKE,
	P_SNOW,
	P_SMOKE,
	P_TOTAL
};

class ParticleObject
{
public:
	ParticleObject(ParticleObject_TYPE = P_SNOW);
	~ParticleObject();

	ParticleObject_TYPE  type; // Particle Type
	Vector3 pos; // Position
	Vector3 vel; // Velocity
	Vector3 scale; // Scale
	float rotation;
	float rotationSpeed;

	bool active;
};

#endif // !PARTICLE_H
