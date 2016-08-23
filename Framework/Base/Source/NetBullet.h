#ifndef NET_BULLET_H
#define NET_BULLET_H

#include "Bullet.h"
class Player;

class NetBullet : public Bullet
{
public:
	NetBullet();
	virtual ~NetBullet();

	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
	void SetPlayer(Player* player);
private:
	Player* player;
};

#endif