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
	virtual ~Weapon();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Shoot(Bullet::ELEMENT element, TileMap* map);
	virtual bool Overheating();

	void setFireRate(float fireRate);
	float getFireRate();

	void setCoolDown(float coolDown);
	float getCoolDown();

	void setDamage(int damage);
	int getDamage();

	void setWeaponType(WEAPON_TYPE weaponType);
	WEAPON_TYPE getWeaponType();

	void setOverHeatRate(float overHeatRate);
	int getOverHeatRate();

	void ReferencePlayerPos(Vector3* pos);
	void ReferencePlayerView(Vector3* view);

protected:
	float defaultFireRate;
	float fireRate;

	float coolDown;
	float overHeatingRate;

	int damage;

	bool overHeat;
	float gunForce;

	WEAPON_TYPE weaponType;
	Vector3 *playerPos, *playerView;

	float offset;
	Vector3 fineOffset;
};



#endif 