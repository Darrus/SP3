#ifndef BOSS_H
#define BOSS_H

#include "GameObject.h"

class Boss : public GameObject
{
public:
	Boss();
	~Boss();

	virtual void Init();
	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);

private:
	void Phase1();
	void Phase2();
};

#endif