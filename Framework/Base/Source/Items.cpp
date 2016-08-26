#include "Items.h"
#include "Player.h"

Items::Items()
{
	collider.Init(&this->pos, scale);
}

Items::~Items()
{

}

void Items::Update(double dt)
{
	collider.Update();

	//timer -= (float)(dt);

	/*if (timer < 0.f)
		player->setPlayerSpeed(100);

	std::cout << timer << std::endl;*/
}

//int Items::GetSpeedPotionCount(void)
//{
//	return SpeedPotionCount;
//}
//
//void Items::SetSpeedPotionCount(int SpeedPotionCount)
//{
//	this->SpeedPotionCount = SpeedPotionCount;
//}
//
//int Items::GetJumpPotionCount(void)
//{
//	return JumpPotionCount;
//}
//
//void Items::SetJumpPotionCount(int JumpPotionCount)
//{
//	this->JumpPotionCount = JumpPotionCount;
//}


void Items::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (player)
	{
		if (collider.CheckCollision(player->collider))
		{
			//Add to inventory
		}
	}
}

bool Items::UseItem(Player* player)
{
	return false;
	/*this->player = player;
	if (itemList == POTIONS)
	{
		int tempHealth = player->GetPlayerHealth();
		if (tempHealth <= player->GetPlayerMaxHealth())
		{
			if (HealthPotionCount > 0 && isUsed == true)
			{
				HealthPotionCount--;
				int gainHp = 25;
				tempHealth += gainHp;
				player->SetPlayerHealth(tempHealth);
			}
			else if (HealthPotionCount <= 0)
			{
				isUsed = false;
			}
		}
	}*/

	//else if (itemList == SPEEDBOOST)
	//{
	//	if (SpeedPotionCount > 0 && isUsed == true)
	//	{
	//		SpeedPotionCount--;
	//		int gainSpeed = 100;
	//		float tmpSpeed = player->getPlayerSpeed();
	//		tmpSpeed += gainSpeed;
	//		player->setPlayerSpeed(tmpSpeed);

	//		/*for (float coolDown = 0; coolDown < 100; coolDown--)
	//		{
	//			if (coolDown <= 0)
	//			{
	//				tmpSpeed -= gainSpeed;
	//				break;
	//			}
	//			std::cout << coolDown << std::endl;
	//		}*/
	//		
	//	}
	//}

}

void Items::cycleItems()
{
	//itemList = (ITEMLIST)((itemList + 1) % (int)ITEMSIZE);
}