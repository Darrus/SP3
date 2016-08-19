#include "Pistol.h"
#include "MeshGenerator.h"

Pistol::Pistol()
{
	fireRate = 0;
	coolDown = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::PISTOL;
	overHeat = false;
	overHeatingRate = 0;
	mesh = MeshGenerator::GetInstance().GenerateQuad("weapon",Color(1,1,1) , "Image//pistol.tga",1.5f);
	offset = 15.f;
	fineOffset.Set(0.f, -2.f, 0.f);
}

Pistol::~Pistol()
{

}

void Pistol::Update(double dt)
{
	Weapon::Update(dt);
}

bool Pistol::overHeating()
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

void Pistol::firingWeapon(Bullet bullet, bool overHeat, double dt)
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
					bullet.vel = bullet.getBulletSpeed() * dt;
					overHeatingRate += 2 * dt;
					bullet.vel += bullet.getBulletSpeed() * (float)dt;
					overHeatingRate += 2 * (float)dt;

					damage = 20;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::ICE)
				{
					bullet.vel += bullet.getBulletSpeed() * (float)dt;
					overHeatingRate += 2 * (float)dt;
					damage = 10;
				}
				if (bullet.getBulletElement() == Bullet::ELEMENT::LIGHTNING)
				{
					bullet.vel += bullet.getBulletSpeed() * (float)dt;
					overHeatingRate += 2 * (float)dt;
					damage = 15;
				}
				fireRate = 0;
			}
		}
	}
}