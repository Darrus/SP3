#ifndef Sniper_H
#define Sniper_H
#include "Weapon.h"

class Sniper : public Weapon
{
public:
	Sniper();
	~Sniper();

	virtual bool Shoot(ELEMENTS element, TileMap* map);
};



#endif 