#include "LevelEditor.h"

LevelEditor::LevelEditor() :
editor(NULL)
{

}

LevelEditor::~LevelEditor()
{
	if (editor)
		delete editor;
	editor = NULL;
}

void LevelEditor::Init()
{
	SceneBase::Init();

	editor = new MapEditor();
	editor->LoadTileSheet("tilesheet", 16, 16);
	editor->Init(m_screenWidth, m_screenHeight, 32);
	editor->SetCamera(&camera);
	editor->active = true;

	camera.Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));
	camera.SetMap(editor->GetMap());
}

void LevelEditor::Update(double dt)
{
	SceneBase::Update(dt);
	if (editor->active)
		editor->Update(dt);
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
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
	RenderEditor();
}

void LevelEditor::Exit()
{
	SceneBase::Exit();
}

// Renders

void LevelEditor::RenderEditor()
{
	if (editor->GetMap())
	{
		int m = 0;
		int n = 0;
		for (int i = 0; i < editor->GetMap()->GetNumOfTiles_ScreenHeight() + 1; i++)
		{
			n = camera.GetTileOffset()->y + i;
			if (n >= editor->GetMap()->GetNumOfTiles_MapHeight())
				break;

			for (int k = 0; k < editor->GetMap()->GetNumOfTiles_ScreenWidth() + 1; k++)
			{
				m = camera.GetTileOffset()->x + k;
				if (m >= editor->GetMap()->GetNumOfTiles_MapWidth())
					break;

				if (editor->GetMap()->rearMap[n][m] > 0 && editor->showMap[0])
					RenderTile(editor->tileSheet, editor->GetMap()->rearMap[n][m], k * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->x, i * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->y, editor->GetMap()->GetTileSize());

				if (editor->GetMap()->frontMap[n][m] > 0 && editor->showMap[1])
					RenderTile(editor->tileSheet, editor->GetMap()->frontMap[n][m], k * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->x, i * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->y, editor->GetMap()->GetTileSize());

				if (editor->GetMap()->collisionMap[n][m] > 0 && editor->showMap[2])
					RenderTile(editor->collisionbox, editor->GetMap()->collisionMap[n][m], k * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->x, i * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->y, editor->GetMap()->GetTileSize());
			}
		}
	}

	if (editor->showTiles)
	{
		modelStack.PushMatrix();
		modelStack.Translate(60.f, m_screenHeight * 0.5f, 0.f);
		modelStack.Scale(120.f, m_screenHeight * 1.1f, 1.f);
		RenderMesh(editor->mapbackground);
		modelStack.PopMatrix();

		int moveX = 11.f;
		for (int i = 0; i < editor->row; ++i)
		{
			for (int k = 0; k < editor->column; ++k)
			{
				RenderTile(editor->tileSheet, editor->tilesID[i][k], k * editor->GetMap()->GetTileSize() + moveX, m_screenHeight - editor->GetMap()->GetTileSize() - (i - editor->offset.y) * editor->GetMap()->GetTileSize(), editor->GetMap()->GetTileSize());
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