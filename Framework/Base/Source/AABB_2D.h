#ifndef AABB_2D_H
#define AABB_2D_H

#include "Collider.h"
#include "Vector3.h"

class AABB_2D : public Collider
{
public:
	AABB_2D();
	~AABB_2D();

	virtual void Init(Vector3 pos, Vector3 scale);
	virtual void UpdateCollider(Vector3 pos);
	virtual bool CheckCollision(AABB_2D* col) const;

private:
	Vector3 min, max;
};

#endif