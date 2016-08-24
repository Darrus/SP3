#include "BurnStatus.h"
#include "ParticleFactory.h"
#include <istream>

using std::stringstream;
BurnStatus::BurnStatus() :
particle(NULL)
{
	duration = 5.f;
	timeBetweenBurn = 0.f;
	name = "Burn";
}

BurnStatus::~BurnStatus()
{
	if (particle)
		particle->active = false;
}

void BurnStatus::Update(double dt)
{
	Status::Update(dt);
	timeBetweenBurn -= dt;
	if (timeBetweenBurn < 0.f)
	{
		enemy->TakeDamage(damage);
		timeBetweenBurn = 1.f;
		stringstream ss;
		ss << damage;
		ParticleFactory::CreateText(ss.str(), 1.f, Vector3(enemy->pos.x, enemy->pos.y + enemy->scale.y * 0.5f, enemy->pos.z), Vector3(20.f, 20.f, 1.f));
	}
}

void BurnStatus::ApplyStatus(GameObject* go)
{
	enemy = dynamic_cast<Enemy*>(go);
	damage = 0.05 * enemy->GetMaxHealth();
	//particle = ParticleFactory::CreateFollow(P_BURN, enemy);
}