#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "Weapon.h"

class Shotgun : public Weapon
{
public:
	Shotgun();
	virtual ~Shotgun();
	virtual void Shoot(Bullet::ELEMENT element, TileMap* map);
};



#endif 