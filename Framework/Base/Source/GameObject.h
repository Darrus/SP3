#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"
#include "Mesh.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);

	Mesh* mesh;

	Vector3 pos;
	Vector3 view;
	Vector3 scale;
	Vector3 vel;

	bool active;
};

#endif