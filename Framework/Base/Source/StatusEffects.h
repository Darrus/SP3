#ifndef STATUS_EFFECTS_H
#define STATUS_EFFECTS_H

#include <vector>
#include <map>
#include <string>
#include "Status.h"

using std::vector;
using std::string;
using std::map;
using std::pair;

class StatusEffects
{
	map<string, Status*> statusList;
	GameObject* go;

public:
	StatusEffects(GameObject* go = NULL);
	~StatusEffects();

	void SetObject(GameObject* go);
	void AddStatus(Status* status);
	void AddImmune(string name);
	void Update(double dt);
};

#endif