#ifndef CAMERA_FREE_H
#define CAMERA_FREE_H

#include "Camera.h"
#include "TileMap.h"
#include "Vector2.h"

class CameraFree : public Camera
{
public:
	CameraFree();
	~CameraFree();

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
	
	Vector2 GetTileOffset();
	Vector2 GetFineOffset();

	void SetMap(TileMap* map);

private:
	void Boundary();

	TileMap* map;

	Vector2 tileOffset;
	Vector2 fineOffset;

	const float CAMERA_SPEED;
};

#endif