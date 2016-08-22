#ifndef RIFLE_H
#define RIFLE_H
#include "Weapon.h"

class Rifle : public Weapon
{
public:
	Rifle();
	~Rifle();

	virtual void Init();
	virtual void Update(double dt);
	virtual bool Overheating();
	virtual void Shoot(Bullet::ELEMENT element, TileMap* map);

};

#endif 