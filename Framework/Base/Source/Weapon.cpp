#include "Weapon.h"
#include "GoManager.h"

Weapon::Weapon()
{
	fireRate = 0;
	coolDown = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::NONE;
	overHeat = false;
	overHeatingRate = 0;
}

Weapon::~Weapon()
{

}

void Weapon::update(double dt)
{

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
	return false;
}

void Weapon::firingWeapon(Bullet bullet, bool overHeat, double dt)
{ 
}

