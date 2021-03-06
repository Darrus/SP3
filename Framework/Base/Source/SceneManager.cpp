#include "SceneManager.h"

#include <iostream>

using std::cout;
using std::endl;

// Scenes
#include "LevelEditor.h"
#include "SceneGameOver.h"
#include "SceneMainMenu.h"
#include "SceneUpgrade.h"
#include "SceneHell.h"
#include "SceneEarth.h"
#include "EarthBoss.h"
#include "SceneHeaven.h"
#include "HeavenBoss.h"
#include "HellBoss.h"
#include "SceneCredit.h"

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
	Scene* newScene = new SceneHeaven();
	AddScene("Heaven", newScene);
	newScene = new HeavenBoss();
	AddScene("HeavenBoss", newScene);
	
	newScene = new SceneEarth();
	AddScene("Earth", newScene);
	newScene = new EarthBoss();
	AddScene("EarthBoss", newScene);

	newScene = new SceneHell();
	AddScene("Hell", newScene);
	newScene = new HellBoss();
	AddScene("HellBoss", newScene);
	
	newScene = new LevelEditor();
	AddScene("LevelEditor", newScene);
	
	newScene = new SceneGameOver();
	AddScene("GameOver", newScene);
	
	newScene = new SceneMainMenu();
	AddScene("MainMenu", newScene);
	
	newScene = new SceneUpgrade();
	AddScene("SceneUpgrade", newScene);

	newScene = new SceneCredit();
	AddScene("SceneCredit", newScene);
	
	currentScene = FindScene("MainMenu");
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

bool SceneManager::CheckChange()
{
	if (changeScene)
	{
		map<string, Scene*>::iterator it = scenes.find(changeName);
		if (it != scenes.end())
		{
			currentScene->Exit();
			currentScene = it->second;
			return true;
		}
		else
		{
			cout << "Scene " << changeName << " does not exist" << endl;
			changeScene = false;
			return false;
		}
	}
	return false;
}

Scene* SceneManager::FindScene(string name)
{
	map<string, Scene*>::iterator it = scenes.find(name);
	if (it != scenes.end())
		return it->second;
	return NULL;
}