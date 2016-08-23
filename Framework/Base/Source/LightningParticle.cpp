#include "LightningParticle.h"

LightningParticle::LightningParticle()
{
	scale.Set(10.f, 5.f, 1.f);
}

LightningParticle::~LightningParticle()
{

}

void LightningParticle::Update(double dt)
{
	if (scale.y > 0)
		scale.y -= dt;
	else if (scale.y < 0)
		active = false;
}