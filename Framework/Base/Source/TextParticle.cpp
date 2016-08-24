#include "TextParticle.h"

TextParticle::TextParticle()
{
	type = P_TEXT;
	duration = 0.5f;
}

TextParticle::~TextParticle()
{

}

void TextParticle::Update(double dt)
{
	duration -= dt;
	if (duration < 0)
		active = false;
	pos.y += 20 * dt;
}