#include "SlowStatus.h"
#include "ParticleFactory.h"
#include "ParticleManager.h"
#include "SoundEngine.h"

SlowStatus::SlowStatus() :
particle(NULL)
{
	duration = 5.f;
	name = "Slow";
	SoundEngine::GetInstance().AddSound("slow", "Sound//slow.mp3");
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
		ParticleFactory::CreateText("Slowed!", 1.f, enemy->pos, Vector3(15.f, 15.f, 1.f));
		SoundEngine::GetInstance().Play("slow");
	}

}

void SlowStatus::RevertStatus()
{
	if (enemy)
		enemy->SetSpeed(enemy->GetDefaultSpeed());
	particle->active = false;
}