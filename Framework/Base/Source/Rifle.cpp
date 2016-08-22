#include "Rifle.h"
#include "MeshGenerator.h"
#include "BulletFactory.h"
#include "Application.h"

Rifle::Rifle()
{
	fireRate = 0.f;
	defaultFireRate = 0.1f;
	damage = 20;
	bulletSpeed = 200.f;
	weaponType = WEAPON_TYPE::RIFLE;
	overheated = false;
	cooldownRate = 20;
	overheatRate = 10;
	scale.Set(40, 20, 1);
	mesh = MeshGenerator::GetInstance().GenerateQuad("Rifle", Color(1.f, 1.f, 1.f), "Image//Rifle.tga", 1.f);
	offset = 15.f;
	fineOffset.Set(0.f, -2.f, 0.f);
}

Rifle::~Rifle()
{

}