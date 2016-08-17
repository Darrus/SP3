#include "SceneManager.h"

#include <iostream>

using std::cout;
using std::endl;

// Scenes
#include "SP3.h"
#include "LevelEditor.h"

SceneManager::SceneManager() :
quit(false),
changeScene(false)
{
	currentScene = nullptr;
}

SceneManager::~SceneManager()
{
	for (map<string, Scene*>::iterator it = scenes.begin(); it != scenes.end();)
	{
		delete it->second;
		it->second = NULL;
		it = scenes.erase(it);
	}
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::Init()
{
	quit = false;
	Scene* newScene = new LevelEditor();
	AddScene("LevelEditor", newScene);;
	newScene = new SP3();
	AddScene("SP3", newScene);
	currentScene = FindScene("LevelEditor");
}

void SceneManager::Update(double dt)
{
	currentScene->Update(dt);
}

void SceneManager::Render()
{
	currentScene->Render();
}

void SceneManager::Exit()
{
	for (map<string, Scene*>::iterator it = scenes.begin(); it != scenes.end();)
	{
		it->second->Exit();
		delete it->second;
		it = scenes.erase(it);
	}
}

void SceneManager::AddScene(string name, Scene* scene)
{
	map<string, Scene*>::iterator it = scenes.find(name);
	if (it == scenes.end())
		scenes.insert(pair<string, Scene*>(name, scene));
	else
		cout << "Scene " << name << " already exist" << endl;
}

void SceneManager::RemoveScene(string name)
{
	map<string, Scene*>::iterator it = scenes.find(name);
	if (it != scenes.end())
	{
		it->second->Exit();
		delete it->second;
		scenes.erase(it);
	}
	else
		cout << "Scene " << name << " does not exist" << endl;
}

void SceneManager::ChangeScene(string name)
{
	changeScene = true;
	changeName = name;
}

void SceneManager::InitCurrent()
{
	if (currentScene)
	{
		currentScene->Init();
		changeScene = false;
	}
}

void SceneManager::ExitCurrent()
{
	if (currentScene)
		currentScene->Exit();
}

void SceneManager::CheckChange()
{
	if (changeScene)
	{
		map<string, Scene*>::iterator it = scenes.find(changeName);
		if (it != scenes.end())
		{
			currentScene->Exit();
			currentScene = it->second;
		}
		else
		{
			cout << "Scene " << changeName << " does not exist" << endl;
			changeScene = false;
		}
	}
}

Scene* SceneManager::FindScene(string name)
{
	map<string, Scene*>::iterator it = scenes.find(name);
	if (it != scenes.end())
		return it->second;
}