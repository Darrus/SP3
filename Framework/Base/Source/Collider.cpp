#include "Collider.h"

Collider::Collider()
{
	pos.SetZero();
	scale.Set(1.f, 1.f, 1.f);
}

Collider::~Collider()
{

}


Vector3 Collider::GetPos()
{
	return this->pos;
}

Vector3 Collider::GetScale()
{
	return this->scale;
}

COLLIDER_TYPE Collider::GetType()
{
	return this->type;
}

void Collider::SetPos(Vector3 pos)
{
	this->pos = pos;
}

void Collider::SetScale(Vector3 scale)
{
	this->scale = scale;
}

void Collider::SetType(COLLIDER_TYPE type)
{
	this->type = type;
}
