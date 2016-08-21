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

	void setBulletSpeed(float bulletSpeed);
	float getBulletSpeed();

	void setBulletElement(ELEMENT bulletElement);
	ELEMENT getBulletElement();

	void SetMap(TileMap* map);

protected:
	void CheckCollision();

	float bulletSpeed;
	int damage;
	ELEMENT bulletElement;
	GameObject object;
	TileMap* map;
};

#endif