#include "Bullet.h"

Bullet::Bullet()
{
	bulletSpeed = 100;
	bulletElement = ELEMENT::NONE;
}

Bullet::~Bullet()
{

}

void Bullet::update(double dt)
{

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