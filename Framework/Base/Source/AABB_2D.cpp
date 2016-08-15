#include "AABB_2D.h"

AABB_2D::AABB_2D()
{
	min.SetZero();
	max.SetZero();
	
}

AABB_2D::~AABB_2D()
{

}

void AABB_2D::Init(Vector3 pos, Vector3 scale)
{
	SetPos(pos);
	SetScale(scale);
	this->min = GetPos() - GetScale() * 0.5f;
	this->max = GetPos() + GetScale() * 0.5f;
}

void AABB_2D::UpdateCollider(Vector3 pos)
{
	this->min = pos - GetScale() * 0.5f;
	this->max = pos + GetScale() * 0.5f;
}

bool AABB_2D::CheckCollision(AABB_2D* col) const
{
	return (max.x >= col->min.x && 
		min.x <= col->max.x &&
		max.y >= col->min.y &&
		min.y <= col->max.y);
}