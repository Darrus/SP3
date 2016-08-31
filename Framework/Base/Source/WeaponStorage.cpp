#include "WeaponStorage.h"
#include "Pistol.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"

WeaponStorage::WeaponStorage()
{
	weapon[0] = new Pistol();

	weapon[1] = new Rifle();

	weapon[2] = new Shotgun();

	weapon[3] = new Sniper();

	std::cout << weapon + 1 << std::endl;
}

WeaponStorage::~WeaponStorage()
{

}

Weapon** WeaponStorage::GetWeapon()
{
	return weapon;
}