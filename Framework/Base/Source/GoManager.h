#ifndef GO_MANAGER_H
#define GO_MANAGER_H

#include <vector>
#include "GameObject.h"

using std::vector;

class GoManager
{
public:
	GoManager();
	~GoManager();

	static GoManager &GetInstance();
	vector<GameObject*>& GetList();
	
	void Add(GameObject* go);
	void Update(double dt);
	void ClearList();
	int GetObjCount();
	GameObject* FetchGO();

private:
	vector<GameObject*> m_goList;
	int objCount;
};

#endif