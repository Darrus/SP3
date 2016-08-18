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

	pistol.pos.Set(player->pos.x + 6, player->pos.y - 5, player->pos.z);
	pistol.scale.Set(16,16,16);

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
	
	fps = 0.f;

	bulletRate = 1;
}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);

	camera->Update(dt);

	//Get mouse pos in world
	double mouseX, mouseY;
	Application::GetInstance().GetMousePos(mouseX, mouseY);
	double worldX, worldY;
	mouseY = m_screenHeight - mouseY;
	worldX = mouseX + camera->position.x;
	worldY = mouseY + camera->position.y;
	player->SetMousePos((float)worldX, (float)worldY);
	player->Update(dt);
	GoManager::GetInstance().Update(dt);

	pistol.update(dt);
	bulletRate += dt;

	

	if (player->getState() == 1)
	{
		pistol.pos.Set(player->pos.x + 6, player->pos.y - 5, player->pos.z);
	}
	else if (player->getState() == 2)
	{
		pistol.pos.Set(player->pos.x - 6, player->pos.y - 5, player->pos.z);
	}
	fps = 1 / dt;

	if (Application::IsMousePressed(0) && bulletRate > 0.2f)
	{
		bullet = new Bullet;
		GoManager::GetInstance().Add(bullet);
		bullet->active = true;
		bullet->type = GameObject::GO_BULLET;
		bullet->scale.Set(1, 1, 1);
		bullet->pos = player->pos;
		
		Vector3 dir = player->view;

		bullet->vel = dir * 100;
		if (bullet->vel.LengthSquared() > 100 * 100)
		{
			bullet->vel.Normalize();
			bullet->vel *= 100;
		}
		bulletRate = 0.f;
	}
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

	RenderMap(map);
	RenderObject(player);

	if (player->getState() == 1)
	{
		modelStack.PushMatrix();
		RenderObject(&pistol);
		modelStack.PopMatrix();
	}


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