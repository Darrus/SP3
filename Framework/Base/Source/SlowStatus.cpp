#include "SlowStatus.h"

SlowStatus::SlowStatus()
{
	duration = 5.f;
	name = "Slow";
}

SlowStatus::~SlowStatus()
{

}

void SlowStatus::Update(double dt)
{
	Status::Update(dt);
}

void SlowStatus::ApplyStatus(GameObject* go)
{
	enemy = dynamic_cast<Enemy*>(go);
	if (enemy)
		enemy->SetSpeed(enemy->GetDefaultSpeed() / 2);
}

void SlowStatus::RevertStatus()
{
	if (enemy)
		enemy->SetSpeed(enemy->GetDefaultSpeed());
}