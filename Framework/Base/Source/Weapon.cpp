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
	bulletSpeed = 0.f;
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

void Weapon::setDefaultFireRate(float defaultFireRate)
{
	this->defaultFireRate = defaultFireRate;
}

float Weapon::getDefaultFireRate()
{
	return this->defaultFireRate;
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

float Weapon::GetOverheatRate()
{
	return this->overheatRate;
}

void Weapon::setOverheatRate(float overheatRate)
{
	this->overheatRate = overheatRate;
}

float Weapon::GetCoolDownRate()
{
	return this->cooldownRate;
}

void Weapon::SetCoolDownRate(float cooldownRate)
{
	this->cooldownRate = cooldownRate;
}
bool Weapon::Overheating()
{
	return this->overheated;
}

bool Weapon::Shoot(ELEMENTS element, TileMap* map)
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
		return true;
	}
	return false;
}

void Weapon::ReferencePlayerPos(Vector3* pos)
{
	playerPos = pos;
}

void Weapon::ReferencePlayerView(Vector3* view)
{
	playerView = view;
}

