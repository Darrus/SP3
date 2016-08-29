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
		MAINMENU,
		STATES_END,
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

	void MenuSelection();
	void InstructionSelection();
	void LevelEditorSelection();

	MENUSTATES MenuStates;
	int selectedOption;
	int InstructionsPage;
	int LevelEditorPage;
};

#endif