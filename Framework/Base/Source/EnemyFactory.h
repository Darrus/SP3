#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "Enemy.h"
#include "TileMap.h"

class EnemyFactory
{ 
public:
	EnemyFactory();
	~EnemyFactory();
	static Enemy* Create(const string& name, Vector3 pos, TileMap* map);
};

#endif