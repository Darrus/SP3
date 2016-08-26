#ifndef AABB_2D_H
#define AABB_2D_H

#include "Vector3.h"

class AABB_2D
{
public:
	AABB_2D();
	~AABB_2D();

	virtual void Init(Vector3* objPos, Vector3 scale);
	virtual void Init(Vector3 pos, Vector3 scale);
	virtual void Update();
	virtual bool CheckCollision(AABB_2D col) const;
	virtual bool CheckCollision(Vector3 point) const;

private:
	Vector3 min, max;
	Vector3 halvedScale;
	Vector3* objPos;
	Vector3 pos;
	Vector3 offset;
};

#endif