#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector3.h"

enum COLLIDER_TYPE
{
	COL_BALL,
	COL_AABB,
};

class Collider
{
private:
	Vector3 pos;
	Vector3 scale;
	COLLIDER_TYPE type;

public:
	Collider();
	virtual ~Collider();

	virtual void Init() = 0;
	virtual void UpdateCollider() = 0;
	virtual bool CheckCollision() const = 0;

	virtual Vector3 GetPos();
	virtual Vector3 GetScale();
	virtual COLLIDER_TYPE GetType();

	virtual void SetPos(Vector3 pos);
	virtual void SetScale(Vector3 scale);
	virtual void SetType(COLLIDER_TYPE type);
};

#endif