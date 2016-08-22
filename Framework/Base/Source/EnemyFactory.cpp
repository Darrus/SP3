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
		enemy->SetWalkLeftAnim(15, 17, 1.f);
		enemy->SetWalkRightAnim(27, 29, 1.f);
		enemy->SetAlertRange(50.f);
		enemy->SetPatrolRange(200.f);
		enemy->SetDefaultSpeed(100.f);
		enemy->SetAttackDamage(10.f);
		enemy->SetAttackRange(40.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(100);
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "Random")
	{
		//Enemy* enemy = Create(name, pos, map);
		//return enemy;
	}
	return NULL;
}