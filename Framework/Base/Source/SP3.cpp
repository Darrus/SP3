#include "SP3.h"
#include "Application.h"
#include "SceneManager.h"
#include "MeshGenerator.h"
#include <sstream>
#include "GoManager.h"

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

	player.Init(map);
	player.pos.Set(50.f, 100.f, 0.f);
	player.scale.Set(32.f, 32.f, 32.f);

	pistol.pos.Set(player.pos.x + 6, player.pos.y - 5, player.pos.z);
	pistol.scale.Set(16,16,16);

	camFollow = new CameraFollow();
	camFollow->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));
	camFollow->LookAt(&player);
	camFollow->SetMap(map);
	camera = camFollow;

	//go = GoManager::GetInstance().FetchGO();
	//go->active == false;

	direction.Set(0,1,0);
	
	/*for (unsigned i = 0; i < 100; i++)
	{
		GoManager::GetInstance().GetList().push_back(new GameObject());
	}*/

	fps = 0.f;

	bulletRate = 1;
}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);
	camera->Update(dt);
	player.Update(dt);
	pistol.update(dt);
	GoManager::GetInstance().Update(dt);

	bulletRate += dt;

	if (player.getState() == 1)
	{
		pistol.pos.Set(player.pos.x + 6, player.pos.y - 5, player.pos.z);
	}
	else if (player.getState() == 2)
	{
		pistol.pos.Set(player.pos.x - 6, player.pos.y - 5, player.pos.z);
	}
	fps = 1 / dt;

	if (Application::IsMousePressed(0) && bulletRate > 0.2f)
	{
		//bullet.pos.Set(pistol.pos.x, pistol.pos.x, pistol.pos.z);
		bullet = new Bullet;
		GoManager::GetInstance().Add(bullet);
		bullet->active = true;
		bullet->type = GameObject::GO_BULLET;
		bullet->scale.Set(1, 1, 1);
		bullet->pos = player.pos;
		Vector3 dir = player.view;

		/*if (!dir.IsZero())
		{
 			dir.Normalize();
		}
		else
		{
			dir.Set(0, 1, 0);
		}*/

		bullet->vel = dir * 100;
		if (bullet->vel.LengthSquared() > 100 * 100)
		{
			bullet->vel.Normalize();
			bullet->vel *= 100;
		}
		bulletRate = 0.f;
	}



	/*pistol.firingWeapon(bullet, pistol.overHeating(), dt);*/

	//if (Application::GetInstance().controller->IsKeyPressed(JUMP))
		//SceneManager::GetInstance().ChangeScene("LevelEditor");
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
	RenderObject(&player);

	if (player.getState() == 1)
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
			//if (go->type == GameObject::GO_BULLET)
			//{
				RenderObject(go);
			//}
		}
	}



	int test = player.pos.y - player.scale.y * 0.5f;

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