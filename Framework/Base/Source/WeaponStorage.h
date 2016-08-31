#ifndef WEAPONSTORAGE_H
#define WEAPONSTORAGE_H

#include "Weapon.h"

class WeaponStorage
{
public:
	static WeaponStorage& GetInstance()
	{
		static WeaponStorage storage;
		return storage;
	}

	virtual ~WeaponStorage();

	Weapon** GetWeapon();

private:
	WeaponStorage();
	Weapon* weapon[4];
};








#endif