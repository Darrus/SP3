#ifndef WEAPON_H
#define WEAPON_H
#include "Bullet.h"

class Weapon : public GameObject
{
public:

	enum WEAPON_TYPE
	{
		PISTOL = 0,
		RIFLE,
		SMG,
		RPG,
		SHOTGUN,
		GPMG,
		SNIPER,
		TRAPGUN,
		NONE,
	};

	Weapon();
	virtual~Weapon();

	virtual void update(double dt);
	virtual bool overHeating();
	virtual void firingWeapon(Bullet bullet, bool overHeat, double dt);

	void setFireRate(float fireRate);
	float getFireRate();

	void setCoolDown(float coolDown);
	float getCoolDown();

	void setDamage(int damage);
	int getDamage();

	void setWeaponType(WEAPON_TYPE weaponType);
	WEAPON_TYPE getWeaponType();

	void setOverHeatRate(int overHeatRate);
	int getOverHeatRate();


private:
	float fireRate;
	float coolDown;
	int damage;
	int overHeatingRate;
	bool overHeat;
	WEAPON_TYPE weaponType;
	Bullet *bullet;
	Bullet bullets;
	//GameObject weapon;
	//Player player;
};



#endif 