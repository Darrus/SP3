#include "StatusEffects.h"

StatusEffects::StatusEffects(GameObject* go)
{
	this->go = go;
	statusList.clear();
}

StatusEffects::~StatusEffects()
{
	map<string, Status*>::iterator it = statusList.begin();
	while (it != statusList.end())
	{
		if (it->second)
			delete it->second;
		it = statusList.erase(it);
	}
}

void StatusEffects::SetObject(GameObject* go)
{
	this->go = go;
}

void StatusEffects::AddStatus(Status* status)
{
	map<string, Status*>::iterator it = statusList.find(status->GetName());
	if (it != statusList.end())
	{
		if (it->second)
		{
			it->second->SetDuration(status->GetDuration());
			delete status;
		}
	}
	else
	{
		status->ApplyStatus(go);
		statusList.insert(pair<string, Status*>(status->GetName(), status));
	}
}

void StatusEffects::AddImmune(string name)
{
	statusList.insert(pair<string, Status*>(name, NULL));
}

void StatusEffects::Update(double dt)
{
	for (map<string, Status*>::iterator it = statusList.begin(); it != statusList.end();)
	{
		if (it->second)
		{
			it->second->Update(dt);
			if (it->second->end)
			{
				it->second->RevertStatus();
				delete it->second;
				it->second = NULL;
				it = statusList.erase(it);
				continue;
			}
		}
		++it;
	}
}
