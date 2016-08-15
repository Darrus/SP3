#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "TileMap.h"
#include "SpriteAnimation.h"

class Player : public GameObject
{
	enum PLAYER_STATE
	{
		P_IDLE,
		P_WALK_RIGHT,
		P_WALK_LEFT,
		P_CLIMB,
		P_JUMP,
	};

public:
	Player();
	~Player();

	virtual void Init(TileMap* map);
	virtual void Update(double dt);
	SpriteAnimation* GetMesh();

private:
	void Move(double dt);
	void CollisionCheck(double dt);

	const float PLAYER_SPEED;
	bool isGrounded;
	bool isMoving;
	bool isClimbing;

	SpriteAnimation* mesh;
	TileMap* map;
	Vector3 newPos;
	PLAYER_STATE state;
};

#endif