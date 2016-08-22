#include "Bullet.h"
#include "MeshGenerator.h"
#include "Application.h"
#include "Enemy.h"

Bullet::Bullet()
{
	scale.Set(10.f, 10.f, 10.f);
	bulletElement = NONE;
	bulletSpeed = 750.f;
	damage = 10;
	active = true;
}

Bullet::~Bullet()
{

}

void Bullet::Update(double dt)
{
	vel.y -= 2.f;
	pos += vel * dt;
	CheckCollision();
}

void Bullet::HandleInteraction(GameObject* go, double dt)
{
	Enemy* enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
	{
		float dist = (enemy->pos - pos).LengthSquared();
		float size = enemy->scale.x + scale.x;
		if (dist < size * size)
		{
			enemy->TakeDamage(damage);
			active = false;
		}
	}
}

void Bullet::SetMap(TileMap* map)
{
	this->map = map;
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

void Bullet::CheckCollision()
{
	// Init Variables
	int tileSize = map->GetTileSize();
	int currentX, currentY;
	currentX = currentY = 0;

	// Make sure object doesnt move out of screen
	if (pos.x - scale.x * 0.5f <= 0 || pos.x + scale.x * 0.5f >= map->GetMapWidth() ||
		pos.y - scale.y * 0.5f <= 0 || pos.y + scale.y * 0.5f >= map->GetMapHeight())
	{
		active = false;
		return;
	} 

	// Get Current Tile
	currentX = pos.x / tileSize;
	currentY = pos.y / tileSize;

	if (map->collisionMap[currentY][currentX] != 0 && active)
		active = false;
}