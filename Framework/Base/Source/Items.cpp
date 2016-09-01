#include "Items.h"
#include "Player.h"

Items::Items()
{
	scale.Set(32.f, 32.f, 32.f);
	collider.Init(&this->pos, scale);
}

Items::~Items()
{

}

void Items::Update(double dt)
{
	collider.Update();
}


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

bool Items::UseItem()
{
	return false;
}

void Items::cycleItems()
{

}