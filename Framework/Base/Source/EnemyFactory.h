#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "Enemy.h"
#include "TileMap.h"

class EnemyFactory
{ 
public:
	enum ENEMY_TYPES
	{
		Goblin,
		WarriorGoblin,
		RangeGoblin,
		BigGoblin,

		Angel,
		RangeAngel,
		BigAngel,
		BigRangeAngel,

		Demon,
		RangeDemon,
		BigDemon,
		BigRangeDemon,
		ENEMY_SIZE
	};

	EnemyFactory();
	~EnemyFactory();
	static Enemy* Create(const string& name, Vector3 pos, TileMap* map);

private:
	static string GetName(ENEMY_TYPES type);
};

#endif