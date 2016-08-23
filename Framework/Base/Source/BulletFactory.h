#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include "Bullet.h"

class Player;

class BulletFactory
{
public:
	BulletFactory();
	~BulletFactory();
	static Bullet* Create(ELEMENTS elem, Vector3 pos, Vector3 dir, float speed, float damage, TileMap* map);
	static Bullet* CreateNet(Vector3 pos, Vector3 dir, Player* player, TileMap* map);
	static Bullet* CreateEnemyBullet(string imageLoc, TileMap* map);
};

#endif