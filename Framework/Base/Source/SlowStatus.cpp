#include "SlowStatus.h"
#include "ParticleFactory.h"
#include "ParticleManager.h"

SlowStatus::SlowStatus() :
particle(NULL)
{
	duration = 5.f;
	name = "Slow";
}

SlowStatus::~SlowStatus()
{
	ParticleManager::GetInstance().Remove(particle);
}

void SlowStatus::Update(double dt)
{
	Status::Update(dt);
}

void SlowStatus::ApplyStatus(GameObject* go)
{
	enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
	{
		enemy->SetSpeed(enemy->GetDefaultSpeed() / 2);
		particle = ParticleFactory::CreateFollow(P_SLOW, enemy);
	}

}

void SlowStatus::RevertStatus()
{
	if (enemy)
		enemy->SetSpeed(enemy->GetDefaultSpeed());
	particle->active = false;
}