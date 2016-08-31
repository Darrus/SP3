#include "Shotgun.h"
#include "MeshGenerator.h"
#include "BulletFactory.h"
#include "Application.h"
#include "SoundEngine.h"
#include "Mtx44.h"

Shotgun::Shotgun()
{
	fireRate = 0.f;
	defaultFireRate = 0.6f;
	cooldownRate = 20;
	damage = 20;
	weaponType = WEAPON_TYPE::SHOTGUN;
	overheated = false;
	overheatRate = 30;
	scale.Set(40, 20, 1);
	mesh = MeshGenerator::GetInstance().GenerateQuad("Shotgun", Color(1.f, 1.f, 1.f), "Image//Shotgun.tga", 1.f);
	SoundEngine::GetInstance().AddSound("Shotgun", "Sound//Shotgun.mp3");
	offset = 15.f;
	fineOffset.Set(0.f, -2.f, 0.f);
}

Shotgun::~Shotgun()
{

}

bool Shotgun::Shoot(ELEMENTS element, TileMap* map)
{
	if (fireRate < 0.f)
	{
		Mtx44 rotate;

		rotate.SetToRotation(0, 0, 0, 1);
		Bullet* bullet1 = BulletFactory::Create(element, pos, view, bulletSpeed, damage, map);
		rotate.SetToRotation(10, 0, 0, 1);
		Bullet* bullet2 = BulletFactory::Create(element, pos, rotate* view, bulletSpeed, damage, map);
		rotate.SetToRotation(-10, 0, 0, 1);
		Bullet* bullet3 = BulletFactory::Create(element, pos, rotate* view, bulletSpeed, damage, map);
		rotate.SetToRotation(-20, 0, 0, 1);
		Bullet* bullet4 = BulletFactory::Create(element, pos, rotate* view, bulletSpeed, damage, map);
		rotate.SetToRotation(20, 0, 0, 1);
		Bullet* bullet5 = BulletFactory::Create(element, pos, rotate* view, bulletSpeed, damage, map);
		fireRate = defaultFireRate;
		overheatBar += overheatRate;
		if (overheatBar > 100.f)
		{
			overheated = true;
			overheatBar = 100.f;
		}
		SoundEngine::GetInstance().Play("Shotgun");
		return true;
	}
	return false;
}