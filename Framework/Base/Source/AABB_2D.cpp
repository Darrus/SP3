#include "AABB_2D.h"

AABB_2D::AABB_2D()
{
	min.SetZero();
	max.SetZero();
	halvedScale.Set(1.f, 1.f, 1.f);
	objPos = NULL;
	pos.SetZero();
}

AABB_2D::~AABB_2D()
{

}

void AABB_2D::Init(Vector3* objPos, Vector3 scale)
{
	this->objPos = objPos;
	pos = *objPos;
	this->halvedScale = scale * 0.5f;
	this->min.Set(pos.x - halvedScale.x, pos.y - halvedScale.y, 1.f);
	this->max.Set(pos.x + halvedScale.x, pos.y + halvedScale.y, 1.f);
}

void AABB_2D::Update()
{
	pos = *objPos;
	min.Set(pos.x - halvedScale.x, pos.y - halvedScale.y, 1.f);
	max.Set(pos.x + halvedScale.x, pos.y + halvedScale.y, 1.f);
}

bool AABB_2D::CheckCollision(AABB_2D col) const
{
	return (max.x >= col.min.x && 
		min.x <= col.max.x &&
		max.y >= col.min.y &&
		min.y <= col.max.y);
}

bool AABB_2D::CheckCollision(Vector3 point) const
{
	return (max.x >= point.x &&
		min.x <= point.x &&
		max.y >= point.y &&
		min.y <= point.y);
}