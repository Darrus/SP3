#include "EnemyStun.h"
#include "EnemyIdle.h"

EnemyStun::EnemyStun()
{
	end = false;
}

EnemyStun::~EnemyStun()
{

}

EnemyStates* EnemyStun::CheckState()
{
	EnemyIdle* idle = new EnemyIdle();
	if (end)
		return idle;
	return this;
}

void EnemyStun::Enter(Enemy* enemy, Player* player)
{
	enemy->vel.x = 0.f;
}