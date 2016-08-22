#include "BurnStatus.h"

BurnStatus::BurnStatus()
{
	duration = 5.f;
	timeBetweenBurn = 0.f;
	name = "Burn";
}

BurnStatus::~BurnStatus()
{

}

void BurnStatus::Update(double dt)
{
	Status::Update(dt);
	timeBetweenBurn -= dt;
	if (timeBetweenBurn < 0.f)
	{
		enemy->TakeDamage(damage);
		timeBetweenBurn = 1.f;
	}
}

void BurnStatus::ApplyStatus(GameObject* go)
{
	enemy = dynamic_cast<Enemy*>(go);
	damage = 0.05 * enemy->GetMaxHealth();
}