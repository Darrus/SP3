#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "Weapon.h"

class Shotgun : public Weapon
{
public:
	Shotgun();
	~Shotgun();

	virtual void update(double dt);
	virtual bool overHeating();
	virtual void firingWeapon(Bullet bullet, bool overHeat, double dt);


private:
	float fireRate;
	float coolDown;
	int damage;
	int overHeatingRate;
	bool overHeat;
	WEAPON_TYPE weaponType;
	Bullet *bullet;
	Bullet bullets;
};



#endif 