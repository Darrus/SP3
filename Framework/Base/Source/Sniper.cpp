#include "Sniper.h"
#include "MeshGenerator.h"
#include "BulletFactory.h"
#include "Application.h"
#include "SoundEngine.h"

Sniper::Sniper()
{
	fireRate = 0.f;
	defaultFireRate = 0.2f;
	cooldownRate = 10;
	damage = 300;
	weaponType = WEAPON_TYPE::SNIPER;
	overheated = false;
	overheatRate = 110;
	bulletSpeed = 500;
	scale.Set(40, 20, 1);
	mesh = MeshGenerator::GetInstance().GenerateQuad("Sniper", Color(1.f, 1.f, 1.f), "Image//Sniper.tga", 1.f);
	SoundEngine::GetInstance().AddSound("Sniper", "Sound//Sniper.mp3");
	offset = 15.f;
	fineOffset.Set(0.f, -2.f, 0.f);
}

Sniper::~Sniper()
{

}

bool Sniper::Shoot(ELEMENTS element, TileMap* map)
{
	if (Weapon::Shoot(element, map))
	{
		SoundEngine::GetInstance().Play("Sniper");
		return true;
	}

	return false;
}