#include "Bullet.h"
#include "MeshGenerator.h"
#include "Application.h"
#include "CameraFollow.h"

Bullet::Bullet()
{
	bulletSpeed = 100;
	bulletElement = ELEMENT::FIRE;

	mesh = mesh = MeshGenerator::GetInstance().GenerateQuad("weapon", Color(1, 1, 1), "Image//Bullet.tga", 10.f);
}

Bullet::~Bullet()
{

}

void Bullet::Update(double dt)
{
	pos += vel * dt;

	CameraFollow camera;

	float w = Application::GetWindowWidth() + camera.position.x;

	if (pos.y > Application::GetWindowHeight())
	{
		active = false;
	}
	else if (pos.y < 0)
	{
		active = false;
	}
	if (pos.x > Application::GetWindowWidth())
	{
		active = false;
	}
	else if (pos.x < 0)
	{
		active = false;
	}
}

void Bullet::setBulletElement(ELEMENT bulletElement)
{
	this->bulletElement = bulletElement;
}

Bullet::ELEMENT Bullet::getBulletElement()
{
	return this->bulletElement;
}

void Bullet::setBulletSpeed(float bulletSpeed)
{
	this->bulletSpeed = bulletSpeed;
}

float Bullet::getBulletSpeed()
{
	return this->bulletSpeed;
}