#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
	store.clear();
}

ParticleManager::~ParticleManager()
{
	ClearList();
}

ParticleManager& ParticleManager::GetInstance()
{
	static ParticleManager instance;
	return instance;
}

vector<ParticleObject*>& ParticleManager::GetList()
{
	return store;
}

void ParticleManager::Add(ParticleObject* particle)
{
	store.push_back(particle);
}

void ParticleManager::Update(double dt)
{
	for (int i = 0; i < store.size(); ++i)
	{
		if (store[i]->active)
			store[i]->Update(dt);
		else
		{
			delete store[i];
			store[i] = NULL;
			store.erase(store.begin() + i);
		}
	}
}

void ParticleManager::ClearList()
{
	while (!store.empty())
	{
		delete store.back();
		store.pop_back();
	}
}