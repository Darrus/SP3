#include "NetBullet.h"
#include "Enemy.h"

NetBullet::NetBullet()
{

}

NetBullet::~NetBullet()
{

}

void NetBullet::Update(double dt)
{

}

void NetBullet::HandleInteraction(GameObject* go, double dt)
{
	Enemy* enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
	{
		if ((float)enemy->GetHealth() / (float)enemy->GetMaxHealth() < 0.2f)
		{
			enemy->active = false;
		}
	}
}