#include "Weapon.h"
#include "Application.h"
#include "BulletFactory.h"

Weapon::Weapon()
{
	fireRate = 0;
	coolDown = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::NONE;
	overHeat = false;
	overHeatingRate = 0;
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

void Weapon::setOverHeatRate(float overHeatingRate)
{
	this->overHeatingRate = overHeatingRate;
}

int Weapon::getOverHeatRate()
{
	return this->overHeatingRate;
}

bool Weapon::Overheating()
{
	return false;
}

void Weapon::Shoot(Bullet::ELEMENT element, TileMap* map)
{ 
	if (fireRate < 0.f)
	{
		Bullet* bullet = BulletFactory::Create(element, pos, view, map);
		fireRate = defaultFireRate;
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

