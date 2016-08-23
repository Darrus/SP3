#include "BulletFactory.h"
#include "FireBullet.h"
#include "LightningBullet.h"
#include "IceBullet.h"
#include "LifeStealBullet.h"
#include "EnemyBullet.h"
#include "NetBullet.h"
#include "GoManager.h"
#include "MeshGenerator.h"

BulletFactory::BulletFactory()
{

}

BulletFactory::~BulletFactory()
{

}

Bullet* BulletFactory::Create(ELEMENTS elem, Vector3 pos, Vector3 dir, float speed, float damage, TileMap* map)
{
	Bullet* bullet = NULL;
	switch (elem)
	{
	case NONE:
		bullet = new Bullet();
		bullet->mesh = MeshGenerator::GetInstance().GenerateQuad("Bullet", Color(1, 1, 1), "Image//Bullet.tga", 1.f);
		break;
	case FIRE:
		bullet = new FireBullet();
		bullet->mesh = MeshGenerator::GetInstance().GenerateQuad("Bullet", Color(1, 1, 1), "Image//FireBullet.tga", 1.f);
		break;
	case ICE:
		bullet = new IceBullet();
		bullet->mesh = MeshGenerator::GetInstance().GenerateQuad("Bullet", Color(1, 1, 1), "Image//IceBullet.tga", 1.f);
		break;
	case LIGHTNING:
		bullet = new LightningBullet();
		bullet->mesh = MeshGenerator::GetInstance().GenerateQuad("Bullet", Color(1, 1, 1), "Image//LightningBullet.tga", 1.f);
		break;
	case LIFESTEAL:
		bullet = new LifeStealBullet();
		bullet->mesh = MeshGenerator::GetInstance().GenerateQuad("Bullet", Color(1, 1, 1), "Image//LifeStealBullet.tga", 1.f);
		break;
	}

	if (bullet)
	{
		bullet->pos = pos;
		bullet->vel = dir * (bullet->bulletSpeed + speed);
		bullet->damage += damage;
		bullet->SetMap(map);
		bullet->active = true;
		GoManager::GetInstance().Add(bullet);
	}

	return bullet;
}

Bullet* BulletFactory::CreateNet(Vector3 pos, Vector3 dir, Player* player, TileMap* map)
{
	NetBullet* net = new NetBullet();
	net->SetPlayer(player);
	net->SetMap(map);
	net->vel = dir * net->bulletSpeed;
	net->pos = pos;
	net->active = true;
	net->mesh = MeshGenerator::GetInstance().GenerateQuad("Bullet", Color(1, 1, 1), "Image//Net.tga", 3.f);
	GoManager::GetInstance().Add(net);
	return net;
}

Bullet* BulletFactory::CreateEnemyBullet(string imageLoc, TileMap* map)
{
	Bullet* bullet = new EnemyBullet();
	bullet->active = true;
	bullet->SetMap(map);
	bullet->mesh = MeshGenerator::GetInstance().GenerateQuad("Enemy Bullet", Color(1, 1, 1), imageLoc, 1.f);
	GoManager::GetInstance().Add(bullet);
	return bullet;
}