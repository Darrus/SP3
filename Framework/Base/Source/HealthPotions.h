#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include "Items.h"

class HealthPotion : public Items
{
public:
	HealthPotion();
	virtual ~HealthPotion();
	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
	virtual bool UseItem();

	int GetHealthRegain(void);
	void SetHealthRegain(int healthRegain);

	int GetHealthPotionCount(void);
	void SetHealthPotionCount(int HealthPotionCount);

private:
	int healthRegain;
	bool canUse;
};



#endif