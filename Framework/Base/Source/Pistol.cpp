#include "Pistol.h"
#include "MeshGenerator.h"
#include "Application.h"

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

	overHeatingRate -= 40 * dt;

	if (overHeatingRate < 0)
	{
		overHeatingRate = 0;
	}
	else if (overHeatingRate > 100)
	{
		overHeatingRate = 100;
	}

	if (Application::IsMousePressed(0))
	{
		if (overHeat == false)
		{
			overHeatingRate++;
		}
	}
	if (overHeat == false && overHeatingRate > 100)
	{
		overHeat = true;
	}
	else if (overHeat == true && overHeatingRate < 1)
	{
		overHeat = false;
	}
	std::cout << overHeatingRate << std::endl;
}

bool Pistol::overHeating()
{
	return this->overHeat;
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