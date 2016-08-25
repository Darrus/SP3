#include "Items.h"
#include "Player.h"

Items::Items() :
potionCount(3),
healthRegain(25),
isUsed(true),
itemList(POTIONS)
{
	collider.Init(&this->pos, scale);
}

Items::~Items()
{

}

void Items::Update(double dt)
{
	collider.Update();
}

int Items::GetPotionCount(void)
{
	return potionCount;
}

void Items::SetPotionCount(int potionCount)
{
	this->potionCount = potionCount;
}

int Items::GetHealthRegain(void)
{
	return healthRegain;
}

void Items::SetHealthRegain(int healthRegain)
{
	this->healthRegain = healthRegain;
}


void Items::HandleItemInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (player)
	{
		if (collider.CheckCollision(player->collider))
		{
			potionCount += 1;
			active = false;
		}
	}
}

void Items::UseItem(Player* player)
{
	if (itemList == POTIONS)
	{
		int tempHealth = player->GetPlayerHealth();
		if (tempHealth <= player->GetPlayerMaxHealth())
		{
			if (potionCount > 0 && isUsed == true)
			{
				potionCount--;
				int gainHp = 25;
				tempHealth += gainHp;
				player->SetPlayerHealth(tempHealth);
			}
			else if (potionCount <= 0)
			{
				isUsed = false;
			}
		}
	}
}

void Items::cycleItems()
{
	itemList = (ITEMLIST)((itemList + 1) % (int)ITEMSIZE);
}