#include "CameraFollow.h"

CameraFollow::CameraFollow()
{
	
}

CameraFollow::~CameraFollow()
{

}

void CameraFollow::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->newPos = pos;
	this->target = target;
	this->up = up;
	tileOffset.Set(0, 0);
	fineOffset.Set(0, 0);
}

void CameraFollow::Update(double dt)
{
	newPos.Set(go->pos.x - map->GetScreenWidth() * 0.5f, go->pos.y - map->GetScreenHeight() * 0.5f, 1.f);
	position.Lerp(newPos, dt);
	Boundary();
	tileOffset.Set((int)position.x / map->GetTileSize(), (int)position.y / map->GetTileSize());
	fineOffset.Set((int)position.x % map->GetTileSize(), (int)position.y % map->GetTileSize());
	target.Set(position.x, position.y, 0.f);
}

void CameraFollow::Reset()
{

}

void CameraFollow::SetNewPos(Vector3 newPos)
{
	this->newPos = newPos;
}

void CameraFollow::Boundary()
{
	float boundX = map->GetMapWidth() - map->GetScreenWidth();
	if (boundX < 0.f)
		boundX = 0.f;
	float boundY = map->GetMapHeight() - map->GetScreenHeight();
	if (boundY < 0.f)
		boundY = 0.f;

	if (position.x < 0.f)
		position.x = 0.f;

	if (position.x > map->GetMapWidth() - map->GetScreenWidth())
		position.x = map->GetMapWidth() - map->GetScreenWidth();

	if (position.y < 0.f)
		position.y = 0.f;

	if (position.y > map->GetMapHeight() - map->GetScreenHeight())
		position.y = map->GetMapHeight() - map->GetScreenHeight();
}

void CameraFollow::LookAt(GameObject *go)
{
	this->go = go;
}

void CameraFollow::SetMap(TileMap *map)
{
	this->map = map;
}

Vector2 CameraFollow::GetTileOffset()
{
	return tileOffset;
}

Vector2 CameraFollow::GetFineOffset()
{
	return fineOffset;
}