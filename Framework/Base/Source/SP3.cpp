#include "SP3.h"
#include "Application.h"

SP3::SP3()
{

}

SP3::~SP3()
{

}

void SP3::Init()
{
	SceneBase::Init();
	map = new TileMap();
	map->Init(m_screenHeight, m_screenWidth, 32);
	map->LoadMap("test");
	map->LoadTileSheet("Image//tilesheet.tga");

	player.Init(map);
	player.pos.Set(0.f, 30.f, 0.f);

	camFollow = new CameraFollow();
	camFollow->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));
	camFollow->LookAt(&player);
	camFollow->SetMap(map);

	camFree = new CameraFree();
	camFree->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 1.f), Vector3(0.f, 1.f, 0.f));
	camFree->SetMap(map);
	camera = camFree;
}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);
	camera->Update(dt);
	//player.Update(dt);
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
	//RenderObject(&player);
}

void SP3::Exit()
{
	SceneBase::Exit();
}

// Renders
void SP3::RenderMap(TileMap* map)
{
	float tileSize = map->GetTileSize();
	Vector2 tileOffset = camFree->GetTileOffset();
	Vector2 fineOffset = camFree->GetFineOffset();

	std::cout << tileOffset.x << std::endl;

	int m, n;
	for (int i = 0; i < map->GetNumOfTiles_ScreenHeight(); ++i)
	{
		n = i + tileOffset.y;
		for (int k = 0; k < map->GetNumOfTiles_ScreenWidth() + 1; ++k)
		{
			m = k + tileOffset.x;
			RenderTile(map->GetTileSheet(), map->rearMap[n][m], k * tileSize - fineOffset.x, i * tileSize - fineOffset.y, tileSize);
			RenderTile(map->GetTileSheet(), map->frontMap[n][m], k * tileSize - fineOffset.x, i * tileSize - fineOffset.y, tileSize);
			RenderTile(map->GetTileSheet(), map->collisionMap[n][m], k * tileSize - fineOffset.x, i * tileSize - fineOffset.y, tileSize);
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