#include "Weapon.h"
#include "Application.h"
#include "BulletFactory.h"

Weapon::Weapon()
{
	fireRate = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::NONE;
	cooldownRate = 0.f;
	overheatRate = 0.f;
	overheatBar = 0.f;
	overheated = false;
	scale.Set(16, 16, 16);
}

Weapon::~Weapon()
{

}

void Weapon::Init()
{

}

void Weapon::Update(double dt)
{
	fireRate -= (float)dt;
	view = *playerView;
	pos = *playerPos + (view * offset) + fineOffset;

	if (overheatBar > 0.f)
	{
		overheatBar -= cooldownRate * dt;
		if (overheatBar < 0)
		{
			overheatBar = 0.f;
			overheated = false;
		}
	}
}

void Weapon::setFireRate(float fireRate)
{
	this->defaultFireRate = fireRate;
	this->fireRate = 0.f;
}

float Weapon::getFireRate()
{
	return this->fireRate;
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

float Weapon::GetOverheatBar()
{
	return this->overheatBar;
}

bool Weapon::Overheating()
{
	return this->overheated;
}

void Weapon::Shoot(Bullet::ELEMENT element, TileMap* map)
{ 
	if (fireRate < 0.f)
	{
		Bullet* bullet = BulletFactory::Create(element, pos, view, bulletSpeed, damage, map);
		fireRate = defaultFireRate;
		overheatBar += overheatRate;
		if (overheatBar > 100.f)
		{
			overheated = true;
			overheatBar = 100.f;
		}
	}
}

void Weapon::ReferencePlayerPos(Vector3* pos)
{
	playerPos = pos;
}

void Weapon::ReferencePlayerView(Vector3* view)
{
	playerView = view;
}

