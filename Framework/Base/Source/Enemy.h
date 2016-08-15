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

	void SetIdleAnimation(int start, int end, float time);
	void SetAttackAnimation(int start, int end, float time);
	void SetPlayer(Player* player);

	virtual SpriteAnimation* GetMesh();

protected:
	SpriteAnimation* mesh;
	Animation animIdle;
	Animation animAttack;
	ENEMY_STATE state;
	Player* player;
	float timeBetweenAttack;
	bool attacked;
};

#endif