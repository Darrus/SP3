#ifndef LIGHTNING_BULLET_H
#define LIGHTNING_BULLET_H
#include "Bullet.h"

class LightningBullet : public Bullet
{
public:
	LightningBullet();
	virtual ~LightningBullet();
	virtual void HandleInteraction(GameObject* go, double dt);
	virtual void Update(double dt);
};

#endif