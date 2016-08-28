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

	void MenuSelection();
	void InstructionSelection();

	MENUSTATES MenuStates;
	int selectedOption;
	int page;
};

#endif