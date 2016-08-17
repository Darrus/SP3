#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "SpriteAnimation.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
	enum ENEMY_STATE
	{
		IDLE,
		ATTACK,
	};

	Enemy();
	virtual ~Enemy();

	virtual void Init();
	virtual void Update(double dt);
	//virtual void HandleInteraction(GameObject* go, double dt);

	void SetIdleAnimation(int start, int end, float time);
	void SetAttackAnimation(int start, int end, float time);
	void SetPlayer(Player* player);

	void SetState(ENEMY_STATE state);

protected:
	Animation animIdle;
	Animation animAttack;

	ENEMY_STATE state;

	SpriteAnimation* sprite;

	Player* player;
	float timeBetweenAttack;
	bool attacked;
};

#endif