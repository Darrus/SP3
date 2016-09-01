#include "LevelEditor.h"
#include "SceneManager.h"
#include "CameraFree.h"
#include "Application.h"
#include "MeshGenerator.h"
#include "SoundEngine.h"

LevelEditor::LevelEditor() :
editor(NULL)
{

}

LevelEditor::~LevelEditor()
{
	Exit();
}

void LevelEditor::Init()
{
	SceneBase::Init();
	camera = new CameraFree();
	CameraFree* camFree = dynamic_cast<CameraFree*>(camera);

	SoundEngine::GetInstance().AddRepeatSound("Florina", "Sound//MapleStory_Florina.mp3");
	SoundEngine::GetInstance().Play("Florina");

	editor = new MapEditor();
	editor->LoadTileSheet("tilesheet2", 16, 16);
	editor->Init(&Application::GetInstance().m_window_width, &Application::GetInstance().m_window_height, 32);
	editor->SetCamera(camFree);
	editor->active = true;

	camera->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));

	Application::ShowCursor(true);
}

void LevelEditor::Update(double dt)
{
	SceneBase::Update(dt);
	if (editor->editorState == MapEditor::EDIT)
		camera->Update(dt);

	if (editor->active)
		editor->Update(dt);

	if (Application::GetInstance().controller->OnHold(EXIT))
		SceneManager::GetInstance().ChangeScene("MainMenu");
}

void LevelEditor::Render()
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

	switch (editor->editorState)
	{
	case MapEditor::SETUP:
		RenderSetupMenu();
		break;
	case MapEditor::CREATE:
		RenderCreateMenu();
		break;
	case MapEditor::LOAD:
		RenderLoadMenu();
		break;
	case MapEditor::EDIT:
		RenderEditor();
		break;
	}
}

void LevelEditor::Exit()
{
	SceneBase::Exit();
	if (editor)
		delete editor;
	editor = NULL;

	MeshGenerator::GetInstance().ClearMeshGenerator();
}

// Renders

void LevelEditor::RenderEditor()
{
	CameraFree* camFree = dynamic_cast<CameraFree*>(camera);
	Vector2 tileOffset = camFree->GetTileOffset();
	Vector2 fineOffset = camFree->GetFineOffset();
	int tileSize = editor->GetMap()->GetTileSize();

	if (editor->GetMap())
	{
		int m = 0;
		int n = 0;
		for (int i = 0; i < editor->GetMap()->GetNumOfTiles_ScreenHeight() + 1; i++)
		{
			n = tileOffset.y + i;
			if (n >= editor->GetMap()->GetNumOfTiles_MapHeight())
				break;

			for (int k = 0; k < editor->GetMap()->GetNumOfTiles_ScreenWidth() + 1; k++)
			{
				m = tileOffset.x + k;
				if (m >= editor->GetMap()->GetNumOfTiles_MapWidth())
					break;

				if (editor->GetMap()->rearMap[n][m] > 0 && editor->showMap[0])
					RenderTile(editor->tileSheet, editor->GetMap()->rearMap[n][m], k * tileSize - fineOffset.x, i * tileSize - fineOffset.y, tileSize);

				if (editor->GetMap()->frontMap[n][m] > 0 && editor->showMap[1])
					RenderTile(editor->tileSheet, editor->GetMap()->frontMap[n][m], k * tileSize - fineOffset.x, i * tileSize - fineOffset.y, tileSize);

				if (editor->GetMap()->collisionMap[n][m] > 0 && editor->showMap[2])
					RenderTile(editor->collisionbox, editor->GetMap()->collisionMap[n][m], k * tileSize - fineOffset.x, i * tileSize - fineOffset.y, tileSize);
			}
		}
	}

	if (editor->showTiles)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera->position.x + 60.f, camera->position.y + Application::GetInstance().m_window_height * 0.5f, 0.f);
		modelStack.Scale(120.f, Application::GetInstance().m_window_height * 1.1f, 1.f);
		RenderMesh(editor->mapbackground);
		modelStack.PopMatrix();

		int moveX = 11.f;
		if (editor->GetState() == MapEditor::COLLISION_MAP)
		{
			for (int i = 0; i < 3; ++i)
				RenderTile(editor->collisionbox, i, i * tileSize, Application::GetInstance().m_window_height - tileSize, tileSize);
		}
		else
		{
			for (int i = 0; i < editor->row; ++i)
			{
				for (int k = 0; k < editor->column; ++k)
				{
						RenderTile(editor->tileSheet, editor->tilesID[i][k], k * tileSize + moveX, Application::GetInstance().m_window_height - tileSize - (i - editor->offset.y) * tileSize, tileSize);
				}
			}
		}
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "Editing:", Color(0.f, 1.f, 0.f), 25, 200, 550);
	RenderTile(meshList[GEO_TEXTBOX], 0, Application::GetInstance().m_window_width - 34, Application::GetInstance().m_window_height - 35, 50);

	switch (editor->GetState())
	{
	case MapEditor::FRONT_MAP:
		RenderTextOnScreen(meshList[GEO_TEXT], "Front Map", Color(0.f, 1.f, 0.f), 25, 400, 550);
		RenderTile(editor->tileSheet, editor->selectedTile, Application::GetInstance().m_window_width - 50, Application::GetInstance().m_window_height - 50, 32);
		break;
	case MapEditor::REAR_MAP:
		RenderTextOnScreen(meshList[GEO_TEXT], "Rear Map", Color(0.f, 1.f, 0.f), 25, 400, 550);
		RenderTile(editor->tileSheet, editor->selectedTile, Application::GetInstance().m_window_width - 50, Application::GetInstance().m_window_height - 50, 32);
		break;
	case MapEditor::COLLISION_MAP:
		RenderTextOnScreen(meshList[GEO_TEXT], "Collision Map", Color(0.f, 1.f, 0.f), 25, 400, 550);
		RenderTile(editor->collisionbox, editor->selectedTile, Application::GetInstance().m_window_width - 50, Application::GetInstance().m_window_height - 50, 32);
		break;
	}
}

void LevelEditor::RenderSetupMenu()
{
	RenderObjOnScreen(meshList[GEO_TEXTBOX], 190, 30, 1, 95, 55);
	RenderTextOnScreen(meshList[GEO_TEXT], editor->text, Color(0.f, 1.f, 0.f), 20, 70, 320);

	modelStack.PushMatrix();
	modelStack.Translate(250.f, 150.f, 1.f);
	modelStack.Scale(200.f, 100.f, 1.f);
	RenderMesh(meshList[GEO_TEXTBOX]);
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], "Yes", Color(0.f, 1.f, 0.f), 50, 190.f, 130.f);

	modelStack.PushMatrix();
	modelStack.Translate(550.f, 150.f, 1.f);
	modelStack.Scale(200.f, 100.f, 1.f);
	RenderMesh(meshList[GEO_TEXTBOX]);
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], "No", Color(0.f, 1.f, 0.f), 50, 510.f, 130.f);
}

void LevelEditor::RenderCreateMenu()
{
	RenderObjOnScreen(meshList[GEO_TEXTBOX], 190, 30, 1, 95, 55);
	RenderTextOnScreen(meshList[GEO_TEXT], editor->text, Color(0.f, 1.f, 0.f), 20, 90, 320);
	RenderTextOnScreen(meshList[GEO_TEXT], editor->answer, Color(0.f, 1.f, 0.f), 30, 330, 270);
}

void LevelEditor::RenderLoadMenu()
{
	RenderObjOnScreen(meshList[GEO_TEXTBOX], 190, 30, 1, 95, 55);
	RenderTextOnScreen(meshList[GEO_TEXT], editor->text, Color(0.f, 1.f, 0.f), 20, 60, 320);
	RenderTextOnScreen(meshList[GEO_TEXT], editor->name, Color(0.f, 1.f, 0.f), 30, 260, 270);
}