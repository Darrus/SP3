#include "HealthPotions.h"
#include "Player.h"

HealthPotion::HealthPotion() :
healthRegain(25)
{

}

HealthPotion::~HealthPotion()
{

}

int HealthPotion::GetHealthRegain(void)
{
	return healthRegain;
}

void HealthPotion::SetHealthRegain(int healthRegain)
{
	this->healthRegain = healthRegain;
}

void HealthPotion::Update(double dt)
{

}

void HealthPotion::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (collider.CheckCollision(player->collider))
	{
		this->player = player;
		this->player->inventory.Add(*this);
	}
}

bool HealthPotion::UseItem(Player* player)
{
	this->player = player;
	int tempHealth = player->GetPlayerHealth();
	if (tempHealth <= player->GetPlayerMaxHealth())
	{
		int gainHp = 25;
		tempHealth += gainHp;
		player->SetPlayerHealth(tempHealth);
		return true;
	}
	return false;
}
