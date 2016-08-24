#include "ParticleFactory.h"
#include "MeshGenerator.h"
#include "LightningParticle.h"
#include "TextParticle.h"
#include "ParticleManager.h"
#include "SpriteParticle.h"

ParticleFactory::ParticleFactory()
{

}

ParticleFactory::~ParticleFactory()
{

}

ParticleObject* ParticleFactory::Create(ParticleObject_TYPE type, Vector3 pos, Vector3 view)
{
	ParticleObject* particle = NULL;
	switch (type)
	{
	}

	particle->active = true;
	ParticleManager::GetInstance().Add(particle);
	return particle;
}

ParticleObject* ParticleFactory::CreateFollow(ParticleObject_TYPE type, GameObject* go)
{
	ParticleObject* particle = NULL;
	switch (type)
	{
	case P_BURN:
		particle = new SpriteParticle();
		particle->type = P_BURN;
		particle->objPos = &go->pos;
		particle->scale.Set(go->scale.x, go->scale.y * 1.5f, 1.f);
		SpriteAnimation* sprite = MeshGenerator::GetInstance().GenerateSprite("Burning Sprite", "Image//burn.tga", 4, 8);
		particle->mesh = sprite;
		Animation anim;
		anim.Set(0, 31, 1.f, true, 1, true);
		sprite->SetAnimation(anim);
	}

	particle->active = true;
	ParticleManager::GetInstance().Add(particle);
	return particle;
}

ParticleObject* ParticleFactory::CreateText(string text, float duration, Vector3 pos, Vector3 scale)
{
	TextParticle* particle = new TextParticle();
	particle->pos = pos;
	particle->scale = scale;
	particle->text = text;
	particle->duration = duration;
	particle->active = true;
	ParticleManager::GetInstance().Add(particle);
	return NULL;
}