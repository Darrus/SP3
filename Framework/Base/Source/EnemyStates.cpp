#include "EnemyStates.h"

EnemyStates::EnemyStates()
{

}

EnemyStates::~EnemyStates()
{

}

void EnemyStates::Enter(Enemy* enemy, Player* player)
{
	this->enemy = enemy;
	this->player = player;
}

EnemyStates* EnemyStates::CheckState()
{
	return NULL;
}

void EnemyStates::Update(double dt)
{

}

void EnemyStates::Exit()
{

}