#ifndef RIFLE_H
#define RIFLE_H
#include "Weapon.h"

class Rifle : public Weapon
{
public:
	Rifle();
	~Rifle();

	virtual bool Shoot(ELEMENTS element, TileMap* map);
};

#endif 