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

void EnemyStates::Update(double dt)
{

}

EnemyStates::ENEMY_STATES EnemyStates::GetState()
{
	return state;
}