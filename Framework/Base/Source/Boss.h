#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "TileMap.h"
#include "Player.h"
#include "StatusEffects.h"
#include "AABB_2D.h"

class Boss : public Enemy
{
public:
	Boss();
	~Boss();

	virtual void Init();
	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
};

#endif