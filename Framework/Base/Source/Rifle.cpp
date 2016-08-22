#include "Rifle.h"
#include "MeshGenerator.h"
#include "BulletFactory.h"
#include "Application.h"

Rifle::Rifle()
{
	fireRate = 0.f;
	defaultFireRate = 0.2f;
	coolDown = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::RIFLE;
	overHeat = false;
	overHeatingRate = 0;
	scale.Set(40, 20, 1);
	mesh = MeshGenerator::GetInstance().GenerateQuad("Rifle", Color(1.f, 1.f, 1.f), "Image//Rifle.tga", 1.f);
	offset = 15.f;
	fineOffset.Set(0.f, -2.f, 0.f);
}

Rifle::~Rifle()
{

}

void Rifle::Init()
{

}

void Rifle::Update(double dt)
{
	fireRate -= 2*dt;
	view = *playerView;
	pos = *playerPos + (view * offset) + fineOffset;

	if (overHeat == false)
		overHeatingRate -= 40 * dt;
	else
		overHeatingRate -= 20 * dt;

	if (overHeatingRate < 0)
	{
		overHeatingRate = 0;
	}
	else if (overHeatingRate > 100)
	{
		overHeatingRate = 100;
	}

	if (Application::IsMousePressed(0))
	{
		if (overHeat == false)
		{
			overHeatingRate+=2;
		}
	}
	if (overHeat == false && overHeatingRate > 100)
	{
		overHeat = true;
	}
	else if (overHeat == true && overHeatingRate < 1)
	{
		overHeat = false;
	}
}

bool Rifle::Overheating()
{
	return this->overHeat;
}

void Rifle::Shoot(Bullet::ELEMENT element, TileMap* map)
{
	if (fireRate < 0.f)
	{
		Bullet* bullet = BulletFactory::Create(element, pos, view, map);
		fireRate = defaultFireRate;
	}
}