#include "Pistol.h"
#include "MeshGenerator.h"
#include "BulletFactory.h"
#include "Application.h"
#include "SoundEngine.h"

Pistol::Pistol()
{
	fireRate = 0.f;
	defaultFireRate = 0.5f;
	damage = 20;
	weaponType = WEAPON_TYPE::PISTOL;
	overheated = false;
	overheatRate = 20;
	cooldownRate = 20;
	scale.Set(20, 20, 1);
	mesh = MeshGenerator::GetInstance().GenerateQuad("Pistol", Color(1.f, 1.f, 1.f), "Image//Pistol.tga", 1.f);
	SoundEngine::GetInstance().AddSound("Pistol", "Sound//Pistol.mp3");

	bulletSpeed = 100.f;

	offset = 15.f;
	fineOffset.Set(0.f, -2.f, 0.f);
}

Pistol::~Pistol()
{

}

bool Pistol::Shoot(ELEMENTS element, TileMap* map)
{
	if (Weapon::Shoot(element, map))
	{
		SoundEngine::GetInstance().Play("Pistol");
		return true;
	}

	return false;
}