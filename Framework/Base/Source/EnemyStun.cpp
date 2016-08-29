#include "EnemyStun.h"

EnemyStun::EnemyStun()
{
	state = ENEMY_STUN;
	end = false;
}

EnemyStun::~EnemyStun()
{

}


void EnemyStun::Enter(Enemy* enemy, Player* player)
{
	enemy->vel.x = 0.f;
}