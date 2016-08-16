#include "CameraFree.h"

CameraFree::CameraFree()
{

}

CameraFree::~CameraFree()
{

}

void CameraFree::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	tileOffset.Set(0, 0);
	fineOffset.Set(0, 0);
}

void CameraFree::Update(double dt)
{

}

void CameraFree::Reset()
{

}

void CameraFree::Boundary()
{
	if (position.x < 0.f)
		position.x = 0.f;

	if (position.x > map->GetMapWidth() - map->GetScreenWidth())
		position.x = map->GetMapWidth() - map->GetScreenWidth();

	if (position.y < 0.f)
		position.y = 0.f;

	if (position.y > map->GetMapHeight() - map->GetScreenHeight())
		position.y = map->GetMapHeight() - map->GetScreenHeight();
}