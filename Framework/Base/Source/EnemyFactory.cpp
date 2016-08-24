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
		enemy->Init(map, pos, Vector3(32.f, 32.f, 32.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
		enemy->SetWalkLeftAnim(15, 17, 1.f);
		enemy->SetWalkRightAnim(27, 29, 1.f);
		enemy->SetAlertRange(50.f);
		enemy->SetPatrolRange(200.f);
		enemy->SetDefaultSpeed(100.f);
		enemy->SetAttackDamage(10.f);
		enemy->SetAttackRange(40.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(100);
		enemy->SetElement(FIRE, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "BigGoblin")
	{
		MeleeEnemy* enemy = new MeleeEnemy();
		enemy->Init(map, pos, Vector3(64.f, 64.f, 64.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
		enemy->SetWalkLeftAnim(15, 17, 1.f);
		enemy->SetWalkRightAnim(27, 29, 1.f);
		enemy->SetAlertRange(50.f);
		enemy->SetPatrolRange(200.f);
		enemy->SetDefaultSpeed(100.f);
		enemy->SetAttackDamage(25.f);
		enemy->SetAttackRange(40.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(300);
		enemy->SetElement(FIRE, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "Range")
	{
		RangeEnemy* enemy = new RangeEnemy();
		enemy->Init(map, pos, Vector3(32.f, 32.f, 32.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
		enemy->SetWalkLeftAnim(60, 62, 1.f);
		enemy->SetWalkRightAnim(72, 74, 1.f);
		enemy->SetAlertRange(150.f);
		enemy->SetPatrolRange(200.f);
		enemy->SetAttackRange(150.f);
		enemy->SetAttackDamage(10.f);
		enemy->SetDefaultSpeed(100.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(100);
		enemy->SetElement(LIGHTNING, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "BigRange")
	{
		RangeEnemy* enemy = new RangeEnemy();
		enemy->Init(map, pos, Vector3(64.f, 64.f, 64.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
		enemy->SetWalkLeftAnim(60, 62, 1.f);
		enemy->SetWalkRightAnim(72, 74, 1.f);
		enemy->SetAlertRange(150.f);
		enemy->SetPatrolRange(200.f);
		enemy->SetAttackRange(150.f);
		enemy->SetAttackDamage(25.f);
		enemy->SetDefaultSpeed(100.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(200);
		enemy->SetElement(LIGHTNING, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "Random")
	{
		int choice = Math::RandIntMinMax(0, ENEMY_SIZE - 1);
		string name = GetName((ENEMY_TYPES)choice);
		Enemy* enemy = Create(name, pos, map);
		return enemy;
	}
	return NULL;
}

string EnemyFactory::GetName(ENEMY_TYPES type)
{
	string name;
	switch (type)
	{
	case Goblin:
		name = "Goblin";
		break;
	case Range:
		name = "Range";
		break;
	case BigGoblin:
		name = "BigGoblin";
		break;
	case BigRange:
		name = "BigRange";
		break;
	default:
		name = "";
		break;
	}
	return name;
}