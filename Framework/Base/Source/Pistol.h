#ifndef PISTOL_H
#define PISTOL_H
#include "Weapon.h"

class Pistol : public Weapon
{
public:
	Pistol();
	~Pistol();

	virtual void Init();
	virtual void Update(double dt);
	virtual bool Overheating();
	virtual void Shoot(Bullet::ELEMENT element, TileMap* map);

protected:
	float gunForce;
};

#endif 