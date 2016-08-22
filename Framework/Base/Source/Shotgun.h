#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "Weapon.h"

class Shotgun : public Weapon
{
public:
	Shotgun();
	~Shotgun();

	virtual void Init();
	virtual void Update(double dt);
	virtual bool Overheating();
	virtual void Shoot(Bullet::ELEMENT element, TileMap* map);

};



#endif 