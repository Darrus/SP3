#include "EnemySkill.h"
#include "Boss.h"

EnemySkill::EnemySkill()
{
	state = ENEMY_SKILL;
}

EnemySkill::~EnemySkill()
{

}

void EnemySkill::Enter(Enemy* enemy, Player* player)
{
	this->enemy = enemy;
	this->player = player;
	enemy->vel.x = 0.f;
}

void EnemySkill::Update(double dt)
{
	Boss* boss = dynamic_cast<Boss*>(enemy);
	boss->Skill();
}