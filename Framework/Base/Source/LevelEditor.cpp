#include "LevelEditor.h"
#include "SceneManager.h"
#include "CameraFree.h"
#include "Application.h"
#include "MeshGenerator.h"

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

	editor = new MapEditor();
	editor->LoadTileSheet("tilesheet", 16, 16);
	editor->Init(m_screenWidth, m_screenHeight, 32);
	editor->SetCamera(camFree);
	editor->active = true;

	camera->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));
	camFree->SetMap(editor->GetMap());
}

void LevelEditor::Update(double dt)
{
	SceneBase::Update(dt);
	camera->Update(dt);
	if (editor->active)
		editor->Update(dt);

	if (Application::GetInstance().controller->IsKeyPressed(JUMP))
		SceneManager::GetInstance().ChangeScene("SP3");
}

void LevelEditor::Render()
{
	SceneBase::Render();
	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0.f, m_screenWidth, 0.f, m_screenHeight, -10.f, 10.f);
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

	RenderEditor();
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
		modelStack.Translate(camera->position.x + 60.f, camera->position.y + m_screenWidth * 0.4f, 0.f);
		modelStack.Scale(120.f, m_screenHeight * 1.1f, 1.f);
		RenderMesh(editor->mapbackground);
		modelStack.PopMatrix();

		int moveX = 11.f;
		if (editor->GetState() == MapEditor::COLLISION_MAP)
		{
			for (int i = 0; i < 3; ++i)
				RenderTile(editor->collisionbox, i, i * tileSize, m_screenHeight - tileSize, tileSize);
		}
		else
		{
			for (int i = 0; i < editor->row; ++i)
			{
				for (int k = 0; k < editor->column; ++k)
				{
					RenderTile(editor->tileSheet, editor->tilesID[i][k], k * tileSize + moveX, m_screenHeight - tileSize - (i - editor->offset.y) * tileSize, tileSize);
				}
			}
		}
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "Editing:", Color(0.f, 1.f, 0.f), 25, 140, 15);

	switch (editor->GetState())
	{
	case MapEditor::FRONT_MAP:
		RenderTextOnScreen(meshList[GEO_TEXT], "Front Map", Color(0.f, 1.f, 0.f), 25, 340, 15);
		break;
	case MapEditor::REAR_MAP:
		RenderTextOnScreen(meshList[GEO_TEXT], "Rear Map", Color(0.f, 1.f, 0.f), 25, 340, 15);
		break;
	case MapEditor::COLLISION_MAP:
		RenderTextOnScreen(meshList[GEO_TEXT], "Collision Map", Color(0.f, 1.f, 0.f), 25, 340, 15);
		break;
	}
}