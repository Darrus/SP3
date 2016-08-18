#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "SpriteAnimation.h"
#include "Player.h"
#include "TileMap.h"

class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init(TileMap* map);
	virtual void Update(double dt);
	//virtual void HandleInteraction(GameObject* go, double dt);

	void SetAttackAnimation(int start, int end, float time);
	void SetPlayer(Player* player);

	Vector3 newPos;

	Animation animWalkLeft;
	Animation animWalkRight;
	Animation animAttack;
	SpriteAnimation* sprite;

	bool collidedWall;
protected:
	void MapCollision(double dt);

	TileMap* map;

	Player* player;

	bool isGrounded;
};

#endif