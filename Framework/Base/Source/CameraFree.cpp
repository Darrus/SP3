#include "CameraFree.h"
#include "Application.h"

CameraFree::CameraFree() :
CAMERA_SPEED(100),
map(NULL)
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
	if (Application::GetInstance().controller->OnHold(MOVE_RIGHT))
		position.x += dt * CAMERA_SPEED;

	if (Application::GetInstance().controller->OnHold(MOVE_LEFT))
		position.x -= dt * CAMERA_SPEED;

	if (Application::GetInstance().controller->OnHold(MOVE_UP))
		position.y += dt * CAMERA_SPEED;

	if (Application::GetInstance().controller->OnHold(MOVE_DOWN))
		position.y -= dt * CAMERA_SPEED;

	Boundary();
	target.Set(position.x, position.y, 0.f);
}

void CameraFree::Reset()
{

}

void CameraFree::Boundary()
{
	if (map)
	{
		if (position.x < 0.f)
			position.x = 0.f;

		float boundX = map->GetMapWidth() - map->GetScreenWidth();
		float boundY = map->GetMapHeight() - map->GetScreenHeight();

		if (position.x >= boundX)
			position.x = boundX;

		if (position.y < 0.f)
			position.y = 0.f;

		if (position.y >= boundY)
			position.y = boundY;

		tileOffset.Set((int)position.x / map->GetTileSize(), (int)position.y / map->GetTileSize());
		fineOffset.Set((int)position.x % map->GetTileSize(), (int)position.y % map->GetTileSize());
	}
	
}

Vector2 CameraFree::GetTileOffset()
{
	return tileOffset;
}

Vector2 CameraFree::GetFineOffset()
{
	return fineOffset;
}

void CameraFree::SetMap(TileMap* map)
{
	this->map = map;
}