#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"
#include "TileMap.h"
#include "Element.h"
#include "AABB_2D.h"

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
	AABB_2D collider;
};

#endif