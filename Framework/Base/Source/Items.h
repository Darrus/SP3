#ifndef ITEMS_H
#define ITEMS_H

#include "GameObject.h"
#include "TileMap.h"
#include "AABB_2D.h"

class Player;

class Items : public GameObject
{
public:
	enum ITEMLIST
	{
		POTIONS,
		SPEEDBOOST,
		JUMPBOOST,
		ITEMSIZE,
	};

	Items();
	virtual ~Items();

	int GetHealthRegain(void);
	int GetPotionCount(void);

	void SetPotionCount(int potionCount);
	void SetHealthRegain(int healthRegain);

	virtual void HandleItemInteraction(GameObject* go, double dt);


	virtual void Update(double dt);
	void UseItem(Player* player);

	void cycleItems();

private:


	ITEMLIST itemList;
	TileMap* map;
	AABB_2D collider;
	int potionCount;
	int healthRegain;

	bool isUsed;
};


#endif