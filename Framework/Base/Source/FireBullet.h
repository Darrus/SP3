#ifndef FIRE_BULLET_H
#define FIRE_BULLET_H
#include "Bullet.h"

class FireBullet : public Bullet
{
public:
	FireBullet();
	virtual ~FireBullet();
	virtual void HandleInteraction(GameObject* go, double dt);
	virtual void Update(double dt);
};

#endif