#include "GoManager.h"
#include "Player.h"

GoManager::GoManager() : 
objCount(0)
{

}

GoManager::~GoManager()
{
	while (!m_goList.empty())
	{
		GameObject* go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}

GoManager& GoManager::GetInstance()
{
	static GoManager manager;
	return manager;
}

void GoManager::Update(double dt)
{
	for (unsigned int i = 0; i < m_goList.size(); ++i)
	{
		if (m_goList[i]->active)
		{
			m_goList[i]->Update(dt);
			for (unsigned int k = 0; k < m_goList.size(); ++k)
			{
				if (m_goList[i] == m_goList[k])
					continue;

				if (m_goList[k]->active)
					m_goList[i]->HandleInteraction(m_goList[k], dt);
			}
		}
		else
		{
			delete m_goList[i];
			m_goList.erase(m_goList.begin() + i);
			objCount--;
		}
	}

	//std::cout << objCount << std::endl;
}

void GoManager::Add(GameObject* go)
{
	m_goList.push_back(go);
	objCount++;
}

void GoManager::ClearList()
{
	while (!m_goList.empty())
	{
		GameObject* go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}

vector<GameObject*>& GoManager::GetList()
{
	return m_goList;
}

GameObject* GoManager::FetchGO()
{
	for (std::vector<GameObject*>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject* go = *it;
		if (!go->active)
		{
			objCount++;
			go->active = true;
			return go;
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		m_goList.push_back(new GameObject());
	}

	GameObject* go = *(m_goList.end() - 1);
	go->active = true;
	objCount++;
	return go;
}

int GoManager::GetObjCount()
{
	return objCount;
}