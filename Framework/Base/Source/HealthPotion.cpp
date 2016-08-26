#include "HealthPotions.h"
#include "Player.h"
#include "MeshGenerator.h"
HealthPotion::HealthPotion() :
healthRegain(25)
{
	mesh = MeshGenerator::GetInstance().GenerateQuad("Potion", Color(1.f, 1.f, 1.f), "Image//healthPotion.tga");
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
	collider.Update();
}

void HealthPotion::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (player)
	{
		if (collider.CheckCollision(player->collider))
		{
			this->player = player;
			player->inventory.Add(this);
		}
	}
}

bool HealthPotion::UseItem()
{
	int tempHealth = player->GetPlayerHealth();
	if (tempHealth < player->GetPlayerMaxHealth())
	{
		int gainHp = 25;
		tempHealth += gainHp;
		if (tempHealth > player->GetPlayerMaxHealth())
			tempHealth = player->GetPlayerMaxHealth();
		player->SetPlayerHealth(tempHealth);
		return true;
	}
	return false;
}
