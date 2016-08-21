#ifndef ICE_BULLET_H
#define ICE_BULLET_H
#include "Bullet.h"

class IceBullet : public Bullet
{
public:
	IceBullet();
	virtual ~IceBullet();
	virtual void HandleInteraction(GameObject* go, double dt);
	virtual void Update(double dt);
};

#endif