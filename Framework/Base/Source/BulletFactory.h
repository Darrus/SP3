#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include "Bullet.h"

class BulletFactory
{
public:
	BulletFactory();
	~BulletFactory();
	static Bullet* Create(Bullet::ELEMENT elem, Vector3 pos, Vector3 dir, TileMap* map);
	static Bullet* CreateEnemyBullet(string imageLoc, TileMap* map);
};

#endif