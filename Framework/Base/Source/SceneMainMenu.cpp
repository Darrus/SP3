#include "GL\glew.h"
#include "SceneMainMenu.h"
#include "Application.h"
#include "SceneManager.h"
#include <sstream>
#include "SoundEngine.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

SceneMainMenu::SceneMainMenu()
{
	MenuStates = MAINMENU;
}

SceneMainMenu::~SceneMainMenu()
{
	Exit();
}

void SceneMainMenu::Init()
{
	SceneBase::Init();
	MenuStates = MAINMENU;

	camera = new Camera();
	camera->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));

	SoundEngine::GetInstance().AddRepeatSound("MainMenuTheme", "Sound//MainMenuTheme.mp3", 1.f);
	SoundEngine::GetInstance().Play("MainMenuTheme");

	meshList[GEO_MAINMENU] = MeshBuilder::GenerateQuad("MainMenu", Color(1, 1, 1), 1.f);
	meshList[GEO_MAINMENU]->textureArray[0] = LoadTGA("Image//MainMenu.tga");

	meshList[GEO_INSTRUCTIONS1] = MeshBuilder::GenerateQuad("InsturctionsPage1", Color(1, 1, 1), 1.f);
	meshList[GEO_INSTRUCTIONS1]->textureArray[0] = LoadTGA("Image//InsturctionsPage1.tga");

	meshList[GEO_INSTRUCTIONS2] = MeshBuilder::GenerateQuad("InsturctionsPage2", Color(1, 1, 1), 1.f);
	meshList[GEO_INSTRUCTIONS2]->textureArray[0] = LoadTGA("Image//InsturctionsPage2.tga");

	meshList[GEO_ARROWPOINTER] = MeshBuilder::GenerateQuad("arrowPointer", Color(1, 1, 1), 1.f);
	meshList[GEO_ARROWPOINTER]->textureArray[0] = LoadTGA("Image//arrowPointer.tga");

	meshList[GEO_LEVELEDITOR1] = MeshBuilder::GenerateQuad("MapEditor1", Color(1, 1, 1), 1.f);
	meshList[GEO_LEVELEDITOR1]->textureArray[0] = LoadTGA("Image//MapEditor1.tga");

	meshList[GEO_LEVELEDITOR2] = MeshBuilder::GenerateQuad("MapEditor2", Color(1, 1, 1), 1.f);
	meshList[GEO_LEVELEDITOR2]->textureArray[0] = LoadTGA("Image//MapEditor2.tga");

	meshList[GEO_LEVELSELECT] = MeshBuilder::GenerateQuad("LevelSelect", Color(1, 1, 1), 1.f);
	meshList[GEO_LEVELSELECT]->textureArray[0] = LoadTGA("Image//LevelSelect.tga");

	selectedOption = 0;
	selectedLevel = 0;
	InstructionsPage = 0;
	LevelEditorPage = 0;
}

void SceneMainMenu::Update(double dt)
{
	SceneBase::Update(dt);
	switch (MenuStates)
	{
	case STARTGAME:
		SceneManager::GetInstance().ChangeScene("Earth");
		break;
	case MAINMENU:
		MenuSelection();
		break;
	case INSTRUCTIONS:
		InstructionSelection();
		break;
	case LEVELEDITOR:
		LevelEditorSelection();
		break;
	case LEVELSELECT:
		LevelSelectSelection();
		break;
	}
}

void SceneMainMenu::Render()
{
	SceneBase::Render();
	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0.f, Application::GetInstance().m_window_width, 0.f, Application::GetInstance().m_window_height, -10.f, 10.f);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera->position.x, camera->position.y, camera->position.z,
		camera->target.x, camera->target.y, camera->target.z,
		camera->up.x, camera->up.y, camera->up.z
		);

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	switch (MenuStates)
	{
	case STARTGAME:
	case MAINMENU:
		RenderMainMenu();
		break;
	case INSTRUCTIONS:
		RenderInstruction();
		break;
	case LEVELEDITOR:
		RenderLevelEditor();
		break;
	case LEVELSELECT:
		RenderLevelSelect();
		break;
	}
}

void SceneMainMenu::RenderMainMenu()
{
	modelStack.PushMatrix();
	modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
	modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
	RenderMesh(meshList[GEO_MAINMENU], false);
	modelStack.PopMatrix();

	if (selectedOption == 0)
	{

		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 25, 15, 10, 50, 54);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], -25, 15, 10, 142, 54);
		modelStack.PopMatrix();

	}
	else if (selectedOption == 1)
	{

		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 25, 15, 10, 50, 39);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], -25, 15, 10, 142, 39);
		modelStack.PopMatrix();
	}
	else if (selectedOption == 2)
	{

		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 25, 15, 10, 50, 24);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], -25, 15, 10, 142, 24);
		modelStack.PopMatrix();

	}
	else if (selectedOption == 3)
	{

		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 25, 15, 10, 50, 12);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], -25, 15, 10, 142, 12);
		modelStack.PopMatrix();
	}
}

void SceneMainMenu::RenderInstruction()
{
	if (InstructionsPage == 0)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
		modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
		RenderMesh(meshList[GEO_INSTRUCTIONS1], false);
		modelStack.PopMatrix();
	}

	if (InstructionsPage == 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
		modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
		RenderMesh(meshList[GEO_INSTRUCTIONS2], false);
		modelStack.PopMatrix();
	}
}

void SceneMainMenu::RenderLevelEditor()
{
	if (LevelEditorPage == 0)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
		modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
		RenderMesh(meshList[GEO_LEVELEDITOR1], false);
		modelStack.PopMatrix();
	}
	else if (LevelEditorPage == 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
		modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
		RenderMesh(meshList[GEO_LEVELEDITOR2], false);
		modelStack.PopMatrix();
	}
}

void SceneMainMenu::RenderLevelSelect()
{
	modelStack.PushMatrix();
	modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
	modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
	RenderMesh(meshList[GEO_LEVELSELECT], false);
	modelStack.PopMatrix();


	if (selectedLevel == 0)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Level: Level 01", Color(1.f, 1.f, 1.f), 25, 400, 200);
		RenderTextOnScreen(meshList[GEO_TEXT], "Earth", Color(1.f, 1.f, 1.f), 25, 530, 150);
		RenderTextOnScreen(meshList[GEO_TEXT], "Difficulty: Easy", Color(1.f, 1.f, 1.f), 25, 400, 100);
	}

	else if (selectedLevel == 1)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Level: Level 02", Color(1.f, 1.f, 1.f), 25, 400, 200);
		RenderTextOnScreen(meshList[GEO_TEXT], "Heaven", Color(1.f, 1.f, 1.f), 25, 530, 150);
		RenderTextOnScreen(meshList[GEO_TEXT], "Difficulty: Medium", Color(1.f, 1.f, 1.f), 23, 390, 100);
	}
	else if (selectedLevel == 2)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Level: Level 03", Color(1.f, 1.f, 1.f), 25, 400, 200);
		RenderTextOnScreen(meshList[GEO_TEXT], "Hell", Color(1.f, 1.f, 1.f), 25, 530, 150);
		RenderTextOnScreen(meshList[GEO_TEXT], "Difficulty: Hard", Color(1.f, 1.f, 1.f), 25, 400, 100);
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "Escape to Go Back", Color(1.f, 1.f, 1.f), 25, 300, 20);
}

void SceneMainMenu::MenuSelection()
{

	if (Application::GetInstance().controller->IsKeyPressed(GODOWN) || Application::GetInstance().controller->IsKeyPressed(MOVE_DOWN))
		selectedOption = (selectedOption + 1) % MAINMENU;

	if (Application::GetInstance().controller->IsKeyPressed(GOUP) || Application::GetInstance().controller->IsKeyPressed(MOVE_UP))
	{
		selectedOption = (selectedOption - 1) % MAINMENU;
		if (selectedOption < 0)
			selectedOption = MAINMENU - 1;
	}

	if (Application::GetInstance().controller->IsKeyPressed(EXIT))
	{
		SceneManager::GetInstance().quit = true;
	}

	if (Application::GetInstance().controller->IsKeyPressed(ENTER))
		MenuStates = (MENUSTATES)selectedOption;
}

void SceneMainMenu::InstructionSelection()
{
	if (Application::GetInstance().controller->IsKeyPressed(GORIGHT) || Application::GetInstance().controller->IsKeyPressed(MOVE_RIGHT))
		InstructionsPage = (InstructionsPage + 1) % 2;

	if (Application::GetInstance().controller->IsKeyPressed(GOLEFT) || Application::GetInstance().controller->IsKeyPressed(MOVE_LEFT))
	{
		InstructionsPage = (InstructionsPage - 1) % 2;
		if (InstructionsPage < 0)
			InstructionsPage = 1;
	}

	if (Application::GetInstance().controller->IsKeyPressed(EXIT))
		MenuStates = MAINMENU;

	if (Application::GetInstance().controller->IsKeyPressed(ENTER))
		SceneManager::GetInstance().ChangeScene("Earth");
}

void SceneMainMenu::LevelEditorSelection()
{
	if (selectedOption == 2)
	{
		if (Application::GetInstance().controller->IsKeyPressed(GORIGHT) || Application::GetInstance().controller->IsKeyPressed(MOVE_RIGHT))
			LevelEditorPage = (LevelEditorPage + 1) % 2;

		if (Application::GetInstance().controller->IsKeyPressed(GOLEFT) || Application::GetInstance().controller->IsKeyPressed(MOVE_LEFT))
		{
			LevelEditorPage = (LevelEditorPage - 1) % 2;
			if (LevelEditorPage < 0)
				LevelEditorPage = 1;
		}

		if (Application::GetInstance().controller->IsKeyPressed(EXIT))
			MenuStates = MAINMENU;

		if (Application::GetInstance().controller->IsKeyPressed(ENTER))
			SceneManager::GetInstance().ChangeScene("LevelEditor");
	}
}

void SceneMainMenu::LevelSelectSelection()
{
	if (Application::GetInstance().controller->IsKeyPressed(GORIGHT) || Application::GetInstance().controller->IsKeyPressed(MOVE_RIGHT))
		selectedLevel = (selectedLevel + 1) % LEVEL_END;

	if (Application::GetInstance().controller->IsKeyPressed(GOLEFT) || Application::GetInstance().controller->IsKeyPressed(MOVE_LEFT))
	{
		selectedLevel = (selectedLevel - 1) % LEVEL_END;
		if (selectedLevel < 0)
			selectedLevel = LEVEL_END - 1;
	}

	if (Application::GetInstance().controller->IsKeyPressed(ENTER) && selectedLevel == 0)
		SceneManager::GetInstance().ChangeScene("Earth");

	else if (Application::GetInstance().controller->IsKeyPressed(ENTER) && selectedLevel == 1)
		SceneManager::GetInstance().ChangeScene("Heaven");

	else if (Application::GetInstance().controller->IsKeyPressed(ENTER) && selectedLevel == 2)
		SceneManager::GetInstance().ChangeScene("Hell");

	if (Application::GetInstance().controller->IsKeyPressed(EXIT))
		MenuStates = MAINMENU;

}

void SceneMainMenu::Exit()
{
	SceneBase::Exit();
}

