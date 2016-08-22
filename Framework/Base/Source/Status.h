#ifndef STATUS_H
#define STATUS_H

#include "GameObject.h"
#include <string>

using std::string;

class Status
{
public:
	Status();
	virtual ~Status();

	virtual void Update(double dt);
	virtual void ApplyStatus(GameObject* go);
	virtual void RevertStatus();

	void SetDuration(float duration);
	float GetDuration();
	
	string GetName();
	bool end;
protected:
	float duration;
	string name;
	GameObject* go;
};

#endif