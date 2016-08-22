#include "StunStatus.h"
#include "EnemyStun.h"
#include "EnemyIdle.h"

StunStatus::StunStatus()
{
	duration = 2.f;
	name = "Stun";
}

StunStatus::~StunStatus()
{

}

void StunStatus::Update(double dt)
{
	Status::Update(dt);
}

void StunStatus::ApplyStatus(GameObject* go)
{
	enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
	{
		EnemyStates* stun = new EnemyStun();
		enemy->SetState(stun);
		enemy->GetState()->Enter(enemy, NULL);
	}
}

void StunStatus::RevertStatus()
{
	if (enemy)
		dynamic_cast<EnemyStun*>(enemy->GetState())->end = true;
}