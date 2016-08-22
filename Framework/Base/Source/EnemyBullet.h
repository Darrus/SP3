#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "Bullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet();
	virtual ~EnemyBullet();

	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
};

#endif