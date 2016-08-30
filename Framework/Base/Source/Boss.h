#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy
{
public:
	Boss();
	~Boss();

	virtual void Update(double dt);
	virtual void Attack(Player* player);
	//virtual void HandleInteraction(GameObject* go, double dt);
	virtual void MapCollision(double dt);

	void Skill();
};

#endif