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
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);
	if (sprite)
		sprite->SetAnimation(enemy->GetAttackAnim());
}

void EnemySkill::Update(double dt)
{
	Boss* boss = dynamic_cast<Boss*>(enemy);
	boss->Skill();
}