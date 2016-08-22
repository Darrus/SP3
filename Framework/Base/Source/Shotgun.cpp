#include "Shotgun.h"
#include "MeshGenerator.h"
#include "BulletFactory.h"
#include "Application.h"

Shotgun::Shotgun()
{
	fireRate = 0.f;
	defaultFireRate = 0.2f;
	cooldownRate = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::SHOTGUN;
	overheated = false;
	overheatRate = 0;
	scale.Set(20, 20, 1);
	mesh = MeshGenerator::GetInstance().GenerateQuad("Shotgun", Color(1.f, 1.f, 1.f), "Image//Pistol.tga", 1.f);
	offset = 15.f;
	fineOffset.Set(0.f, -2.f, 0.f);
}

Shotgun::~Shotgun()
{

}