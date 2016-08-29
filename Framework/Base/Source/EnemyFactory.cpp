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
		enemy->SetWalkAnim(27, 29, 1.f);
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
		enemy->SetWalkAnim(27, 29, 1.f);
		enemy->SetAlertRange(50.f);
		enemy->SetPatrolRange(200.f);
		enemy->SetDefaultSpeed(100.f);
		enemy->SetAttackDamage(25.f);
		enemy->SetAttackRange(40.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(300);
		enemy->SetElement(ICE, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}



	if (name == "RangeGoblin")
	{
		RangeEnemy* enemy = new RangeEnemy();
		enemy->Init(map, pos, Vector3(32.f, 32.f, 32.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
		enemy->SetWalkAnim(72, 74, 1.f);
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

	if (name == "BigRangeGoblin")
	{
		RangeEnemy* enemy = new RangeEnemy();
		enemy->Init(map, pos, Vector3(64.f, 64.f, 64.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
		enemy->SetWalkAnim(72, 74, 1.f);
		enemy->SetAlertRange(150.f);
		enemy->SetPatrolRange(200.f);
		enemy->SetAttackRange(150.f);
		enemy->SetAttackDamage(25.f);
		enemy->SetDefaultSpeed(100.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(200);
		enemy->SetElement(LIFESTEAL, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "Angel")
	{
		MeleeEnemy* enemy = new MeleeEnemy();
		enemy->Init(map, pos, Vector3(32.f, 32.f, 32.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Angel", "Image//AngelSprite.tga", 8, 12);
		enemy->SetWalkAnim(81, 83, 1.f);
		enemy->SetAlertRange(50.f);
		enemy->SetPatrolRange(300.f);
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

	if (name == "BigAngel")
	{
		MeleeEnemy* enemy = new MeleeEnemy();
		enemy->Init(map, pos, Vector3(64.f, 64.f, 64.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Big Angel", "Image//AngelSprite.tga", 8, 12);
		enemy->SetWalkAnim(81, 83, 1.f);
		enemy->SetAlertRange(50.f);
		enemy->SetPatrolRange(500.f);
		enemy->SetDefaultSpeed(50.f);
		enemy->SetAttackDamage(25.f);
		enemy->SetAttackRange(40.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(300);
		enemy->SetElement(ICE, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}


	if (name == "RangeAngel")
	{
		RangeEnemy* enemy = new RangeEnemy();
		enemy->Init(map, pos, Vector3(32.f, 32.f, 32.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Range Angel", "Image//AngelSprite.tga", 8, 12);
		enemy->SetWalkAnim(33, 35, 1.f);
		enemy->SetAlertRange(150.f);
		enemy->SetPatrolRange(100.f);
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

	if (name == "BigRangeAngel")
	{
		RangeEnemy* enemy = new RangeEnemy();
		enemy->Init(map, pos, Vector3(64.f, 64.f, 64.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Big Range Angel", "Image//AngelSprite.tga", 8, 12);
		enemy->SetWalkAnim(33, 35, 1.f);
		enemy->SetAlertRange(150.f);
		enemy->SetPatrolRange(100.f);
		enemy->SetAttackRange(150.f);
		enemy->SetAttackDamage(25.f);
		enemy->SetDefaultSpeed(50.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(200);
		enemy->SetElement(LIFESTEAL, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}


	if (name == "Demon")
	{
		MeleeEnemy* enemy = new MeleeEnemy();
		enemy->Init(map, pos, Vector3(64.f, 64.f, 64.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Demon", "Image//DemonSprite.tga", 2, 9);
		enemy->SetWalkAnim(0, 6, 1.f);
		enemy->SetAlertRange(75.f);
		enemy->SetPatrolRange(300.f);
		enemy->SetDefaultSpeed(80.f);
		enemy->SetAttackDamage(30.f);
		enemy->SetAttackRange(40.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(200);
		enemy->SetElement(FIRE, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "BigDemon")
	{
		MeleeEnemy* enemy = new MeleeEnemy();
		enemy->Init(map, pos, Vector3(80.f, 80.f, 80.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Demon", "Image//DemonSprite.tga", 2, 9);
		enemy->SetWalkAnim(0, 6, 1.f);
		enemy->SetAlertRange(75.f);
		enemy->SetPatrolRange(300.f);
		enemy->SetDefaultSpeed(80.f);
		enemy->SetAttackDamage(30.f);
		enemy->SetAttackRange(40.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(300);
		enemy->SetElement(FIRE, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "RangeDemon")
	{
		RangeEnemy* enemy = new RangeEnemy();
		enemy->Init(map, pos, Vector3(64.f, 64.f, 64.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Range Demon", "Image//DemonSprite.tga", 2, 9);
		enemy->SetWalkAnim(0, 6, 1.f);
		enemy->SetAlertRange(100.f);
		enemy->SetPatrolRange(150.f);
		enemy->SetAttackRange(150.f);
		enemy->SetAttackDamage(20.f);
		enemy->SetDefaultSpeed(150.f);
		enemy->SetTimeBetweenAttack(1.f);
		enemy->SetHealth(120);
		enemy->SetElement(LIFESTEAL, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "BigRangeDemon")
	{
		RangeEnemy* enemy = new RangeEnemy();
		enemy->Init(map, pos, Vector3(80.f, 80.f, 80.f));
		enemy->mesh = MeshGenerator::GetInstance().GenerateSprite("Range Demon", "Image//DemonSprite.tga", 2, 9);
		enemy->SetWalkAnim(0, 6, 1.f);
		enemy->SetAlertRange(100.f);
		enemy->SetPatrolRange(200.f);
		enemy->SetAttackRange(100.f);
		enemy->SetAttackDamage(50.f);
		enemy->SetDefaultSpeed(80.f);
		enemy->SetTimeBetweenAttack(0.8f);
		enemy->SetHealth(200);
		enemy->SetElement(LIFESTEAL, 10);
		enemy->active = true;
		GoManager::GetInstance().Add(enemy);
		return enemy;
	}

	if (name == "RandomGoblin")
	{
		int choice = Math::RandIntMinMax(Goblin, BigRange);
		string name = GetName((ENEMY_TYPES)choice);
		Enemy* enemy = Create(name, pos, map);
		return enemy;
	}

	if (name == "RandomAngel")
	{
		int choice = Math::RandIntMinMax(Angel, BigRangeAngel);
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
	case RangeGoblin:
		name = "RangeGoblin";
		break;
	case BigGoblin:
		name = "BigGoblin";
		break;
	case BigRange:
		name = "BigRangeGoblin";
		break;
	case Angel:
		name = "Angel";
		break;
	case RangeAngel:
		name = "RangeAngel";
		break;
	case BigAngel:
		name = "BigAngel";
		break;
	case BigRangeAngel:
		name = "BigRangeAngel";
		break;
	case Demon:
		name = "Demon";
		break;
	case RangeDemon:
		name = "RangeDemon";
		break;
	case BigDemon:
		name = "BigDemon";
		break;
	case BigRangeDemon:
		name = "BigRangeDemon";
		break;
	default:
		name = "";
		break;
	}
	return name;
}