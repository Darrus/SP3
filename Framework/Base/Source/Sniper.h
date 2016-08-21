#ifndef Sniper_H
#define Sniper_H
#include "Weapon.h"

class Sniper : public Weapon
{
public:
	Sniper();
	~Sniper();

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