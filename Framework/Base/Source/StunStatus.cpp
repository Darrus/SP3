#include "StunStatus.h"
#include "EnemyStun.h"
#include "EnemyIdle.h"
#include "ParticleFactory.h"
#include "ParticleManager.h"

StunStatus::StunStatus() :
particle(NULL)
{
	duration = 2.f;
	name = "Stun";
}

StunStatus::~StunStatus()
{
	ParticleManager::GetInstance().Remove(particle);
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
		particle = ParticleFactory::CreateFollow(P_STUN, enemy);
	}
}

void StunStatus::RevertStatus()
{
	if (enemy)
		dynamic_cast<EnemyStun*>(enemy->GetState())->end = true;
	particle->active = false;
}