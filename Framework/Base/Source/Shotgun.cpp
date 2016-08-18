#include "Shotgun.h"

Shotgun::Shotgun()
{
	fireRate = 0;
	coolDown = 0;
	damage = 0;
	//weaponType = WEAPON_TYPE::SHOTGUN;
	overHeat = false;
	overHeatingRate = 0;
}

Shotgun::~Shotgun()
{
}

void Shotgun::update(double dt)
{
	overHeatingRate -= dt;
	fireRate += 0.1 * dt;
	overHeating();
}

bool Shotgun::overHeating()
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

void Shotgun::firingWeapon(Bullet bullet, bool overHeat, double dt)
{
	WEAPON_TYPE tmpWpType = weaponType;
	Bullet tmpBullet = bullet;
	bool tmpOverHeat = overHeat;
	fireRate += (float)dt;

	if (tmpWpType == WEAPON_TYPE::SHOTGUN)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 2)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::FIRE)
				{
					bullet.vel += bullet.getBulletSpeed() * (float)dt;
					overHeatingRate += 2 * (float)dt;
					damage = 5;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * (float)dt;
					overHeatingRate += 2 * (float)dt;
					damage = 2;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * (float)dt;
					overHeatingRate += 2 * (float)dt;
					damage = 3;
				}
				fireRate = 0;
			}
		}
	}
}
