#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include <map>
#include <string>

using std::map;
using std::string;
using std::pair;

class SceneManager
{
private:
	map<string, Scene*> scenes;
	Scene* currentScene;

public:
	SceneManager();
	~SceneManager();

	static SceneManager& GetInstance();

	void Init();
	void Update(double dt);
	void Render();
	void Exit();

	void AddScene(string name, Scene* scene);
	void RemoveScene(string name);
	void ChangeScene(string name);
	bool CheckChange();
	Scene* FindScene(string name);

	void InitCurrent();
	void ExitCurrent();
	
	bool quit;
	bool changeScene;
	string changeName;
};

#endif