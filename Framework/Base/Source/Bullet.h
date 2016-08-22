#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"
#include "TileMap.h"

class Bullet : public GameObject
{
public:

	enum ELEMENT
	{
		NONE,
		FIRE,
		LIGHTNING,
		ICE,
		ELEM_SIZE,
	};

	Bullet();
	virtual ~Bullet();

	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
	void SetMap(TileMap* map);
	void CheckCollision();

	float bulletSpeed;
	int damage;
	ELEMENT bulletElement;
	TileMap* map;
};

#endif