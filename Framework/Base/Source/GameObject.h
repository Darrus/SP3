#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"

#include "Mesh.h"

class GameObject
{
public:
	enum OBJECT_TYPE
	{
		GO_BALL,
		GO_WALL,
	};

	enum COLLIDER_TYPE
	{
		COL_BALL,
		COL_WALL,
		COL_AABB
	};

	GameObject();
	virtual ~GameObject();

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void HandleCollision(GameObject* go, double dt);
	virtual Mesh* GetMesh();

	Vector3 pos;
	Vector3 view;
	Vector3 scale;
	Vector3 normal;
	Vector3 vel;

	float mass;

	COLLIDER_TYPE collider;
	OBJECT_TYPE type;

	bool active, render;
};

#endif