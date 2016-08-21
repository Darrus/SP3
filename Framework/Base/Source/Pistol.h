#ifndef PISTOL_H
#define PISTOL_H
#include "Weapon.h"
#include "Mesh.h"

class Pistol : public Weapon
{
public:
	Pistol();
	~Pistol();

	virtual void Update(double dt);
	virtual bool overHeating();
	virtual void firingWeapon(Bullet bullet, bool overHeat, double dt);

private:
	float fireRate;
	float coolDown;
	int damage;
	float overHeatingRate;
	bool overHeat;
	WEAPON_TYPE weaponType;
	Bullet *bullet;
	Bullet bullets;

};

#endif 