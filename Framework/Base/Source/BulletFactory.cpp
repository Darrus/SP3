#include "BulletFactory.h"
#include "FireBullet.h"
#include "LightningBullet.h"
#include "IceBullet.h"
#include "GoManager.h"
#include "MeshGenerator.h"

BulletFactory::BulletFactory()
{

}

BulletFactory::~BulletFactory()
{

}

Bullet* BulletFactory::Create(Bullet::ELEMENT elem, Vector3 pos, Vector3 dir, TileMap* map)
{
	Bullet* bullet = NULL;
	switch (elem)
	{
	case Bullet::NONE:
		bullet = new Bullet();
		bullet->mesh = MeshGenerator::GetInstance().GenerateQuad("Bullet", Color(1, 1, 1), "Image//Bullet.tga", 1.f);
		break;
	case Bullet::FIRE:
		break;
	case Bullet::ICE:
		break;
	case Bullet::LIGHTNING:
		break;
	}

	if (bullet)
	{
		bullet->pos = pos;
		bullet->vel = dir * bullet->getBulletSpeed();
		bullet->SetMap(map);
		bullet->active = true;
		GoManager::GetInstance().Add(bullet);
	}

	return bullet;
}