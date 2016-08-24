#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include <vector>
#include "Particle.h"

using std::vector;

class ParticleManager
{
private:
	vector<ParticleObject*> store;

public:
	ParticleManager();
	~ParticleManager();

	static ParticleManager &GetInstance();
	vector<ParticleObject*>& GetList();

	void Add(ParticleObject* particle);
	void Remove(ParticleObject* particle);
	void Update(double dt);
	void ClearList();
};

#endif