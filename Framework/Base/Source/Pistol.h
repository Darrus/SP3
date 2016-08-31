#ifndef PISTOL_H
#define PISTOL_H
#include "Weapon.h"

class Pistol : public Weapon
{
public:
	Pistol();
	~Pistol();

	virtual bool Shoot(ELEMENTS element, TileMap* map);
};

#endif 