#include "Sniper.h"

Sniper::Sniper()
{
	fireRate = 0;
	coolDown = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::SNIPER;
	overHeat = false;
	overHeatingRate = 0;
}

Sniper::~Sniper()
{
}

void Sniper::update(double dt)
{
	overHeatingRate -= dt;
	fireRate += 0.1 * dt;
	overHeating();
}

bool Sniper::overHeating()
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

void Sniper::firingWeapon(Bullet bullet, bool overHeat, double dt)
{
	WEAPON_TYPE tmpWpType = weaponType;
	Bullet tmpBullet = bullet;
	bool tmpOverHeat = overHeat;
	fireRate += (float)dt;

	if (tmpWpType == WEAPON_TYPE::SNIPER)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 1.5)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::FIRE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 3 * dt;
					damage = 100;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 3 * dt;
					damage = 70;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 3 * dt;
					damage = 80;
				}
				fireRate = 0;
			}
		}
	}
}