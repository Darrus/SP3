#include "ParticleFactory.h"
#include "MeshGenerator.h"
#include "LightningParticle.h"
#include "ParticleManager.h"

ParticleFactory::ParticleFactory()
{

}

ParticleFactory::~ParticleFactory()
{

}

ParticleObject* ParticleFactory::Create(PARTICLES_TYPE type, Vector3 pos, Vector3 view, GameObject* go)
{
	ParticleObject* particle = NULL;
	switch (type)
	{
	case P_LIGHTNING:
		particle = new LightningParticle();
		particle->pos = pos;
		particle->rotation = Math::RadianToDegree(atan2(view.y, view.x));
		particle->go = go;
	}

	particle->active = true;
	return particle;
}

ParticleObject* ParticleFactory::CreateText(string text, float duration)
{
	return NULL;
}