#include "Rifle.h"

Rifle::Rifle()
{
	fireRate = 0;
	coolDown = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::RIFLE;
	overHeat = false;
	overHeatingRate = 0;
}

Rifle::~Rifle()
{

}

void Rifle::update(double dt)
{
	overHeatingRate -= dt;
	fireRate += 0.1 * dt;
	overHeating();
}

bool Rifle::overHeating()
{
	if (overHeatingRate >= 10)
	{
		return true;
	}
	else if (overHeatingRate <= 0)
	{
		overHeatingRate = 0;
		return false;
	}
	else
	{
		return false;
	}
}

void Rifle::firingWeapon(Bullet bullet, bool overHeat, double dt)
{
	WEAPON_TYPE tmpWpType = weaponType;
	Bullet tmpBullet = bullet;
	bool tmpOverHeat = overHeat;
	fireRate += (float)dt;

	if (tmpWpType == WEAPON_TYPE::RIFLE)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 0.7)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::FIRE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 3 * dt;
					damage = 20;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 3 * dt;
					damage = 10;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 3 * dt;
					damage = 15;
				}
				fireRate = 0;
			}
		}
	}
}