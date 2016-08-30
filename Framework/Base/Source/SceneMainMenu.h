#ifndef SCENEMAINMENU_H
#define SCENEMAINMENU_H

#include "SceneBase.h"

class SceneMainMenu : public SceneBase
{
public:
	enum MENUSTATES
	{
		STARTGAME,
		INSTRUCTIONS,
		LEVELEDITOR,
		LEVELSELECT,
		MAINMENU,
		STATES_END,
	};

	enum LEVELS
	{
		LEVEL1,
		LEVEL2,
		LEVEL3,
		LEVEL_END,
	};

	SceneMainMenu();
	virtual ~SceneMainMenu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMainMenu();
	void RenderInstruction();
	void RenderLevelEditor();
	void RenderLevelSelect();

	void MenuSelection();
	void InstructionSelection();
	void LevelEditorSelection();
	void LevelSelectSelection();

	MENUSTATES MenuStates;
	int selectedOption;
	int selectedLevel;
	int InstructionsPage;
	int LevelEditorPage;
};

#endif