#include "EnemyFactory.h"
#include "GoManager.h"
#include "MeleeEnemy.h"
#include "RangeEnemy.h"
#include "MeshGenerator.h"

EnemyFactory::EnemyFactory()
{

}

EnemyFactory::~EnemyFactory()
{

}

Enemy* EnemyFactory::Create(const string& name, Vector3 pos, TileMap* map)
{
	if (name == "Goblin")
	{
		MeleeEnemy* enemy = new MeleeEnemy();
		enemy->Init(map);
		enemy->pos = pos;
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
		enemy->scale.Set(32.f, 32.f, 32.f);
		enemy->active = true;
		enemy->animWalkLeft.Set(15, 17, 1.f, true, 1, true);
		enemy->animWalkRight.Set(27, 29, 1.f, true, 1, true);
		enemy->AlertRange = 50.f;
		enemy->PatrolRange = 200.f;
		enemy->EnemySpeed = 100.f;
		enemy->AttackDamage = 10.f;
		enemy->TimeBetweenAttack = 1.f;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}
	return NULL;
}