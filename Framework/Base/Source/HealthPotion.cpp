#include "HealthPotions.h"
#include "Player.h"

HealthPotion::HealthPotion() :
HealthPotionCount(3),
healthRegain(25),
isUsed(true)
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

int HealthPotion::GetHealthPotionCount(void)
{
	return HealthPotionCount;
}

void HealthPotion::SetHealthPotionCount(int HealthPotionCount)
{
	this->HealthPotionCount = HealthPotionCount;
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
			if (HealthPotionCount > 0 && isUsed == true)
			{
				HealthPotionCount--;
				int gainHp = 25;
				tempHealth += gainHp;
				player->SetPlayerHealth(tempHealth);
				return true;
			}
			else if (HealthPotionCount <= 0)
			{
				isUsed = false;
				return false;
			}
		}
		return false;
}
