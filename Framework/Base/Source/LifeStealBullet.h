#ifndef LIFESTEALBULLET_H
#define LIFESTEALBULLET_H

#include "Bullet.h"
class Player;

class LifeStealBullet : public Bullet
{
public:
	LifeStealBullet();
	virtual ~LifeStealBullet();

	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
	void SetPlayer(Player* player);
private:
	Player* player;
};

#endif 