#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"
#include "TileMap.h"
#include "Element.h"

class Bullet : public GameObject
{
public:
	Bullet();
	virtual ~Bullet();

	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);
	void SetMap(TileMap* map);
	void CheckCollision();

	float bulletSpeed;
	int lifeStealRate;
	int damage;
	ELEMENTS bulletElement;
	TileMap* map;
};

#endif