#include "Weapon.h"
#include "GoManager.h"

Weapon::Weapon()
{
	fireRate = 0;
	coolDown = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::PISTOL;
	overHeat = false;
	overHeatingRate = 0;
}

Weapon::~Weapon()
{

}

void Weapon::update(double dt)
{
	overHeatingRate -= dt;
	fireRate += 0.1 * dt;
	overHeating();
}

void Weapon::setFireRate(float fireRate)
{
	this->fireRate = fireRate;
}

float Weapon::getFireRate()
{
	return this->fireRate;
}

void Weapon::setCoolDown(float coolDown)
{
	this->coolDown = coolDown;
}

float Weapon::getCoolDown()
{
	return this->coolDown;
}

void Weapon::setDamage(int damage)
{
	this->damage = damage;
}

int Weapon::getDamage()
{
	return this->damage;
}

void Weapon::setWeaponType(WEAPON_TYPE weaponType)
{
	this->weaponType = weaponType;
}

Weapon::WEAPON_TYPE Weapon::getWeaponType()
{
	return this->weaponType;
}

void Weapon::setOverHeatRate(int overHeatingRate)
{
	this->overHeatingRate = overHeatingRate;
}

int Weapon::getOverHeatRate()
{
	return this->overHeatingRate;
}

bool Weapon::overHeating()
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

void Weapon::firingWeapon(Bullet bullet, bool overHeat, double dt)
{
	WEAPON_TYPE tmpWpType = weaponType;
	Bullet tmpBullet = bullet;
	bool tmpOverHeat = overHeat;
	fireRate += (float)dt;

	if (tmpWpType == WEAPON_TYPE::PISTOL)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 1)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::FIRE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 20;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 10;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 15;
				}
				fireRate = 0;
			}
		}
	}
	else if (tmpWpType == WEAPON_TYPE::RIFLE)
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
	else if (tmpWpType == WEAPON_TYPE::SMG)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 0.3)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::FIRE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 4 * dt;
					damage = 15;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 3 * dt;
					damage = 5;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 3 * dt;
					damage = 10;
				}
				fireRate = 0;
			}
		}
	}
	else if (tmpWpType == WEAPON_TYPE::SHOTGUN)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 2)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::FIRE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 5;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 2;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 3;
				}
				fireRate = 0;
			}
		}
	}
	else if (tmpWpType == WEAPON_TYPE::RPG)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 3)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::FIRE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 4 * dt;
					damage = 150;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 4 * dt;
					damage = 100;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 4 * dt;
					damage = 120;
				}
				fireRate = 0;
			}
		}
	}
	else if (tmpWpType == WEAPON_TYPE::SNIPER)
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
	else if (tmpWpType == WEAPON_TYPE::GPMG)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 0.3)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::FIRE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 40;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 30;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					damage = 20;
				}
				fireRate = 0;
			}
		}
	}

	else if (tmpWpType == WEAPON_TYPE::TRAPGUN)
	{
		if (tmpOverHeat == false)
		{
			if (fireRate > 0.3)
			{
				if (bullet.getBulletElement() == Bullet::ELEMENT::TRAPPER)
				{
					bullet.vel += bullet.getBulletSpeed() * dt;
					overHeatingRate += 10 * dt;
					damage = 40;
				}
			}
		}
	}
}

