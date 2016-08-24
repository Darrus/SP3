#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3.h"
#include "GameObject.h"
#include "Mesh.h"

enum ParticleObject_TYPE
{
	P_NORMAL,
	P_TEXT,
	P_TOTAL
};

class ParticleObject
{
public:
	ParticleObject(ParticleObject_TYPE = P_NORMAL);
	~ParticleObject();

	virtual void Update(double dt);

	ParticleObject_TYPE  type; // Particle Type
	Vector3 pos; // Position
	Vector3 vel; // Velocity
	Vector3 scale; // Scale
	float rotation;
	float rotationSpeed;

	GameObject* go;
	Mesh* mesh;
	bool active;
};

#endif // !PARTICLE_H
