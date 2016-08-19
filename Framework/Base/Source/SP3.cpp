#include "SP3.h"
#include "Application.h"
#include "SceneManager.h"
#include "MeshGenerator.h"
#include <sstream>
#include "GoManager.h"
#include "MeleeEnemy.h"


SP3::SP3()
{

}

SP3::~SP3()
{
	Exit();
}

void SP3::Init()
{
	SceneBase::Init();

	map = new TileMap();
	map->Init(m_screenHeight, m_screenWidth, 32);
	map->LoadMap("test");
	map->LoadTileSheet("Image//tilesheet.tga");

	player = new Player();
	player->Init(map);
	player->pos.Set(50.f, 100.f, 0.f);
	player->scale.Set(32.f, 32.f, 32.f);
	player->active = true;
	GoManager::GetInstance().Add(player);

	camFollow = new CameraFollow();
	camFollow->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));
	camFollow->LookAt(player);
	camFollow->SetMap(map);
	camera = camFollow;

	MeleeEnemy* enemy = new MeleeEnemy();
	enemy->Init(map);
	enemy->pos.Set(200.f, 200.f, 0.f);
	enemy->scale.Set(32.f, 32.f, 32.f);
	enemy->active = true;
	GoManager::GetInstance().Add(enemy);

	background.Init(&camera->position,800,600);
	
	fps = 0.f;

	background.LoadBackground("Image//RearBg.tga", Vector3(map->GetMapWidth(), map->GetMapHeight(), 0));
	background.LoadBackground("Image//MidBg.tga", Vector3(map->GetMapWidth(), map->GetMapHeight(), 0));
	background.LoadBackground("Image//FrontBg.tga", Vector3(map->GetMapWidth(), map->GetMapHeight(), 0));
}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);

	//Get mouse pos in world
	Application::GetInstance().GetMousePos(mouseX, mouseY);
	mouseY = m_screenHeight - mouseY;
	worldX = mouseX + camera->position.x;
	worldY = mouseY + camera->position.y;
	player->SetMousePos((float)worldX, (float)worldY);

	camera->Update(dt);
	background.Update();
	GoManager::GetInstance().Update(dt);
	fps = 1 / dt;
}


void SP3::Render()
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

	for (int i = 0; i < background.GetBackgroundCount(); ++i)
	{
		Background* bg = background.GetBackground(i);
		modelStack.PushMatrix();
		modelStack.Translate(bg->GetPosition().x, bg->GetPosition().y, bg->GetPosition().z);
		modelStack.Scale(bg->GetScale().x, bg->GetScale().y, bg->GetScale().z);
		RenderMesh(bg->GetMesh());
		modelStack.PopMatrix();
	}

	RenderMap(map);
	RenderObject(player);
	if (player->GetWeapon())
		RenderWeaponObject(player->GetWeapon());

	for (vector<GameObject *>::iterator it = GoManager::GetInstance().GetList().begin(); it != GoManager::GetInstance().GetList().end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active == true)
		{
			RenderObject(go);
		}
	}

	std::stringstream text;
	text << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], text.str() , Color(0.f, 1.f, 0.f), 20, 10, 10);
}

void SP3::Exit()
{
	SceneBase::Exit();
	if (map)
		delete map;
	map = NULL;
	MeshGenerator::GetInstance().ClearMeshGenerator();
}

// Renders
void SP3::RenderMap(TileMap* map)
{
	float tileSize = map->GetTileSize();
	Vector2 tileOffset = camFollow->GetTileOffset();
	Vector2 fineOffset = camFollow->GetFineOffset();

	int m, n;
	for (int i = 0; i < map->GetNumOfTiles_MapHeight() + 1; ++i)
	{
		n = i + tileOffset.y;

		if (n >= map->GetNumOfTiles_MapHeight())
			break;

		for (int k = 0; k < map->GetNumOfTiles_MapWidth() + 1; ++k)
		{
			m = k + tileOffset.x;

			if (m >= map->GetNumOfTiles_MapWidth())
				break;
			if (map->rearMap[n][m] > 0)
				RenderTile(map->GetTileSheet(), map->rearMap[n][m], k * tileSize - fineOffset.x, i * tileSize - fineOffset.y, tileSize);
			if (map->frontMap[n][m] > 0)
				RenderTile(map->GetTileSheet(), map->frontMap[n][m], k * tileSize - fineOffset.x, i * tileSize - fineOffset.y, tileSize);
		}
	}
}

void SP3::RenderObject(GameObject* go)
{

	modelStack.PushMatrix();
	modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
	modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
	RenderMesh(go->mesh);
	modelStack.PopMatrix();
}


void SP3::RenderWeaponObject(GameObject* go)
{
	if (go->view.x > 0)
	{
		float weaponRot = Math::RadianToDegree(atan2(go->view.y, go->view.x));
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(weaponRot, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(go->mesh);
		modelStack.PopMatrix();
	}
	else
	{
		float weaponRot = Math::RadianToDegree(atan2(go->view.y, go->view.x));
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(180, 1, 0, 0);
		modelStack.Rotate(-weaponRot, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(go->mesh);
		modelStack.PopMatrix();
	}
}