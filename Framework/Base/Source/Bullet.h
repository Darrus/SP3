#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"
//#include "Player.h"

class Bullet:public GameObject
{
public:

	enum ELEMENT
	{
		FIRE = 0,
		LIGHTNING,
		ICE,
		TRAPPER,
		NONE,
	};

	Bullet();
	virtual ~Bullet();

	virtual void Update(double dt);

	void setBulletSpeed(float bulletSpeed);
	float getBulletSpeed();

	void setBulletElement(ELEMENT bulletElement);
	ELEMENT getBulletElement();


protected:
	float bulletSpeed;
	ELEMENT bulletElement;
	GameObject object;

};

#endif