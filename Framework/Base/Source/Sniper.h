#ifndef Sniper_H
#define Sniper_H
#include "Weapon.h"

class Sniper : public Weapon
{
public:
	Sniper();
	~Sniper();
	virtual void Init();
	virtual void Update(double dt);
	virtual bool Overheating();
	virtual void Shoot(Bullet::ELEMENT element, TileMap* map);

};



#endif 