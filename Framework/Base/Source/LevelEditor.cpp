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
	editor->Init(m_screenWidth, m_screenHeight);
	editor->active = true;
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
}

void LevelEditor::Exit()
{
	SceneBase::Exit();
}

// Renders

void LevelEditor::RenderEditor()
{
	if (editor->GetRearMap())
	{
		int m = 0;
		int n = 0;
		for (int i = 0; i < editor->GetRearMap()->GetNumOfTiles_ScreenHeight() + 1; i++)
		{
			n = camera.GetTileOffset()->y + i;
			if (n >= editor->GetRearMap()->GetNumOfTiles_MapHeight())
				break;

			for (int k = 0; k < editor->GetRearMap()->GetNumOfTiles_ScreenWidth() + 1; k++)
			{
				m = camera.GetTileOffset()->x + k;
				if (m >= editor->GetRearMap()->GetNumOfTiles_MapWidth())
					break;

				if (editor->GetRearMap()->theScreenMap[n][m] > 0)
					RenderTile(editor->GetCollisionBox(), editor->GetRearMap()->theScreenMap[n][m], k * editor->GetRearMap()->GetTileSize() - camera.GetFineOffset()->x, i * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->y, editor->GetRearMap()->GetTileSize());
			}
		}
	}

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

				if (editor->GetMap()->theScreenMap[n][m] > 0)
					RenderTile(editor->GetCollisionBox(), editor->GetMap()->theScreenMap[n][m], k * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->x, i * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->y, editor->GetMap()->GetTileSize());
			}
		}
	}

	if (!editor->GetMap()->theCollisionMap.empty())
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

				if (editor->GetMap()->theCollisionMap[n][m] > 0)
					RenderTile(editor->GetCollisionBox(), editor->GetMap()->theCollisionMap[n][m], k * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->x, i * editor->GetMap()->GetTileSize() - camera.GetFineOffset()->y, editor->GetMap()->GetTileSize());
			}
		}
	}

	if (editor->showTiles)
	{
		for (int i = 0; i < editor->row; ++i)
		{
			for (int k = 0; k < editor->column; ++k)
			{
				RenderTile(editor->GetTileSheet(), editor->tilesID[i][k], k * editor->GetMap()->GetTileSize(), m_screenHeight - editor->GetMap()->GetTileSize() - (i - editor->offset.y) * editor->GetMap()->GetTileSize(), editor->GetMap()->GetTileSize());
			}
		}
	}
}