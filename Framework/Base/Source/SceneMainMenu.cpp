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

	Math::InitRNG();

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

	selectedOption = 0;
	InstructionsPage = 0;
	LevelEditorPage = 0;
}

void SceneMainMenu::Update(double dt)
{
	SceneBase::Update(dt);
	switch (MenuStates)
	{
	case STARTGAME:
		SceneManager::GetInstance().ChangeScene("SP3");
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
		modelStack.Translate((Application::GetInstance().m_window_width * 0.5) - 190, (Application::GetInstance().m_window_height * 0.5) - 5, 0);
		modelStack.Scale(100, 100, 1);
		RenderMesh(meshList[GEO_ARROWPOINTER], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate((Application::GetInstance().m_window_width * 0.5) + 190, (Application::GetInstance().m_window_height * 0.5) - 5, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(100, 100, 1);
		RenderMesh(meshList[GEO_ARROWPOINTER], false);
		modelStack.PopMatrix();
	}
	else if (selectedOption == 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate((Application::GetInstance().m_window_width * 0.5) - 190, (Application::GetInstance().m_window_height * 0.5) - 90, 0);
		modelStack.Scale(100, 100, 1);
		RenderMesh(meshList[GEO_ARROWPOINTER], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate((Application::GetInstance().m_window_width * 0.5) + 190, (Application::GetInstance().m_window_height * 0.5) - 90, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(100, 100, 1);
		RenderMesh(meshList[GEO_ARROWPOINTER], false);
		modelStack.PopMatrix();
	}
	else if (selectedOption == 2)
	{
		modelStack.PushMatrix();
		modelStack.Translate((Application::GetInstance().m_window_width * 0.5) - 190, (Application::GetInstance().m_window_height * 0.5) - 170, 0);
		modelStack.Scale(100, 100, 1);
		RenderMesh(meshList[GEO_ARROWPOINTER], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate((Application::GetInstance().m_window_width * 0.5) + 190, (Application::GetInstance().m_window_height * 0.5) - 170, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(100, 100, 1);
		RenderMesh(meshList[GEO_ARROWPOINTER], false);
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

	if (Application::GetInstance().controller->IsKeyPressed(BACKSPACE))
		MenuStates = MAINMENU;

	if (Application::GetInstance().controller->IsKeyPressed(ENTER))
		SceneManager::GetInstance().ChangeScene("SP3");

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

		if (Application::GetInstance().controller->IsKeyPressed(BACKSPACE))
			MenuStates = MAINMENU;

		if (Application::GetInstance().controller->IsKeyPressed(ENTER))
			SceneManager::GetInstance().ChangeScene("LevelEditor");
	}
}

void SceneMainMenu::Exit()
{
	SceneBase::Exit();
}

