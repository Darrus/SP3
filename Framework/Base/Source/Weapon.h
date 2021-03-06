#ifndef WEAPON_H
#define WEAPON_H
#include "Bullet.h"

class Weapon
{
public:
	enum WEAPON_TYPE
	{
		PISTOL = 0,
		RIFLE,
		SHOTGUN,
		SNIPER,
		TRAPGUN,
		NONE,
	};

	Weapon();
	virtual ~Weapon();

	virtual void Init();
	virtual void Update(double dt);
	virtual bool Shoot(ELEMENTS element, TileMap* map);
	virtual bool Overheating();

	void setFireRate(float fireRate);
	float getFireRate();
	void setDefaultFireRate(float defaultFireRate);
	float getDefaultFireRate();

	void setDamage(int damage);
	int getDamage();

	void setWeaponType(WEAPON_TYPE weaponType);
	WEAPON_TYPE getWeaponType();

	float GetOverheatBar();
	float GetOverheatRate();
	void setOverheatRate(float overheatRate);
	float GetCoolDownRate();
	void SetCoolDownRate(float cooldownRate);

	void ReferencePlayerPos(Vector3* pos);
	void ReferencePlayerView(Vector3* view);

	Vector3 pos;
	Vector3 scale;
	Vector3 view;
	Mesh* mesh;

protected:
	float defaultFireRate;
	float fireRate;

	bool overheated;
	float overheatBar;
	float overheatRate;
	float cooldownRate;

	int damage;
	float bulletSpeed;

	WEAPON_TYPE weaponType;
	Vector3 *playerPos, *playerView;

	float offset;
	Vector3 fineOffset;
};



#endif 