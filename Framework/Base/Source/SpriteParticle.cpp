#include "SpriteParticle.h"
#include "SpriteAnimation.h"

SpriteParticle::SpriteParticle()
{

}

SpriteParticle::~SpriteParticle()
{

}

void SpriteParticle::Update(double dt)
{
	pos = *objPos;
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(mesh);
	sprite->Update(dt);
}