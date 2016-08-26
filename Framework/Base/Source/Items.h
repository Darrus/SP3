#ifndef ITEMS_H
#define ITEMS_H

#include "GameObject.h"
#include "TileMap.h"
#include "AABB_2D.h"

class Player;

class Items : public GameObject
{
public:

	Items();
	virtual ~Items();

	int GetSpeedPotionCount(void);
	void SetSpeedPotionCount(int SpeedPotionCount);

	int GetJumpPotionCount(void);
	void SetJumpPotionCount(int JumpPotionCount);


	virtual void HandleInteraction(GameObject* go, double dt);

	virtual void Update(double dt);
	virtual bool UseItem(Player* player);

	void cycleItems();

protected:

	Player* player;
	TileMap* map;
	AABB_2D collider;

	float timer;
	/*int SpeedPotionCount;
	int JumpPotionCount;*/
};


#endif