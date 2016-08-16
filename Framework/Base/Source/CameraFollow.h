#ifndef CAMERA_FOLLOW_H
#define CAMERA_FOLLOW_H

#include "Camera.h"
#include "TileMap.h"
#include "GameObject.h"
#include "Vector2.h"

class CameraFollow: public Camera
{
public:
	CameraFollow();
	~CameraFollow();

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();

	void SetNewPos(Vector3 newPos);
	void SetObject(GameObject *go);
	void SetMap(TileMap *map);

	Vector2* GetTileOffset();
	Vector2* GetFineOffset();

private:
	void Boundary();

	Vector3 newPos;
	Vector2 tileOffset;
	Vector2 fineOffset;
	GameObject *go;
	TileMap* map;
};

#endif