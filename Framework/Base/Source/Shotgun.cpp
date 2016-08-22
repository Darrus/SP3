#include "Shotgun.h"
#include "MeshGenerator.h"
#include "BulletFactory.h"
#include "Application.h"

Shotgun::Shotgun()
{
	fireRate = 0.f;
	defaultFireRate = 0.2f;
	coolDown = 0;
	damage = 0;
	weaponType = WEAPON_TYPE::SHOTGUN;
	overHeat = false;
	overHeatingRate = 0;
	scale.Set(20, 20, 1);
	mesh = MeshGenerator::GetInstance().GenerateQuad("Shotgun", Color(1.f, 1.f, 1.f), "Image//Pistol.tga", 1.f);
	offset = 15.f;
	fineOffset.Set(0.f, -2.f, 0.f);
}

Shotgun::~Shotgun()
{

}

void Shotgun::Init()
{

}

void Shotgun::Update(double dt)
{
	fireRate -= dt;
	view = *playerView;
	pos = *playerPos + (view * offset) + fineOffset;

	overHeatingRate -= 40 * dt;

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
			overHeatingRate++;
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

bool Shotgun::Overheating()
{
	return this->overHeat;
}

void Shotgun::Shoot(Bullet::ELEMENT element, TileMap* map)
{
	if (fireRate < 0.f)
	{
		Bullet* bullet = BulletFactory::Create(element, pos, view, map);
		fireRate = defaultFireRate;
	}
}
