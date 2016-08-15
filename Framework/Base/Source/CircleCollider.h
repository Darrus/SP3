#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

class CircleCollider
{
public:
	CircleCollider();
	~CircleCollider();

	virtual void Init() = 0;
	virtual void UpdateCollider() = 0;
	virtual bool CheckCollision() const = 0;
};

#endif