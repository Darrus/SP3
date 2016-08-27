#ifndef ITEMS_H
#define ITEMS_H

#include "GameObject.h"
#include "TileMap.h"
#include "AABB_2D.h"
#include "SoundEngine.h"

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
	virtual bool UseItem();

	void cycleItems();

	Player* player;
protected:
	AABB_2D collider;
	SoundEngine* sound;

	float timer;
	/*int SpeedPotionCount;
	int JumpPotionCount;*/
};


#endif