#include "EnemyDeath.h"

EnemyDeath::EnemyDeath()
{
	state = ENEMY_DEATH;
}

EnemyDeath::~EnemyDeath()
{

}

void EnemyDeath::Enter(Enemy* enemy, Player* player)
{
	this->enemy = enemy;
	enemy->vel.x = 0.f;
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);
	if (sprite)
		sprite->SetAnimation(enemy->GetDeathAnim());
}

void EnemyDeath::Update(double dt)
{
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(enemy->mesh);
	if (sprite && sprite->m_anim->ended)
		enemy->active = false;
}