#include "SP3.h"
#include "Application.h"
#include "SceneManager.h"
#include "MeshGenerator.h"
#include <sstream>
#include "GoManager.h"
#include "EnemyFactory.h"
#include "ParticleManager.h"
#include "TextParticle.h"



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

	Math::InitRNG();

	map = new TileMap();
	map->Init((int)m_screenHeight, (int)m_screenWidth, 32);
	map->LoadMap("Level01");
	map->LoadTileSheet("Image//tilesheet.tga");

	player = new Player();
	player->Init(map, Vector3(50.f, 100.f, 0.f), Vector3(32.f, 32.f, 32.f));
	player->active = true;
	GoManager::GetInstance().Add(player);

	camFollow = new CameraFollow();
	camFollow->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));
	camFollow->LookAt(player);
	camFollow->SetMap(map);
	camera = camFollow;

	weapon = new Weapon();
	background.Init(&camera->position,800,600);

	EnemyFactory::Create("RandomAngel", Vector3(200.f, 200.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(100.f, 600.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(200.f, 400.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(400.f, 500.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(600.f, 150.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(550.f, 150.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(600.f, 700.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(900.f, 650.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(1000.f, 480.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(1100.f, 300.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(1200.f, 800.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(1400.f, 800.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(1500.f, 200.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(1700.f, 200.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(1700.f, 100.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(2000.f, 100.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(1950.f, 645.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(2340.f, 600.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(2477.f, 400.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(3020.f, 666.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(2724.f, 538.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(2800.f, 794.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(3389.f, 602.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(3219.f, 378.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(3219.f, 100.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(2982.f, 100.f, 0.f), map);
	EnemyFactory::Create("RandomAngel", Vector3(2576.f, 100.f, 0.f), map);
	
	fps = 0.f;

	background.LoadBackground("Image//RearBg.tga", Vector3(1980, 1080, 0));
	background.LoadBackground("Image//MidBg.tga", Vector3(1980, 1080, 0));
	background.LoadBackground("Image//FrontBg.tga", Vector3(1980, 1080, 0));


}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);
	//std::cout << player->pos.x << " " << player->pos.y << std::endl;


	//Get mouse pos in world
	Application::GetInstance().GetMousePos(mouseX, mouseY);
	mouseY = m_screenHeight - mouseY;
	worldX = mouseX + camera->position.x;
	worldY = mouseY + camera->position.y;
	player->SetMousePos((float)worldX, (float)worldY);

	camera->Update(dt);
	background.Update();
	GoManager::GetInstance().Update(dt);
	ParticleManager::GetInstance().Update(dt);
	fps = 1 / (float)dt;
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
		if (go->active)
		{
			RenderObject(go);
			Enemy* enemy = dynamic_cast<Enemy*>(go);
			if (enemy)
			{

			}
		}
	}

	RenderParticle();

	RenderUI();
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
	int tileSize = map->GetTileSize();
	Vector2 tileOffset = camFollow->GetTileOffset();
	Vector2 fineOffset = camFollow->GetFineOffset();

	int m, n;
	for (int i = 0; i < map->GetNumOfTiles_MapHeight() + 1; ++i)
	{
		n = i + (int)tileOffset.y;

		if (n >= map->GetNumOfTiles_MapHeight())
			break;

		for (int k = 0; k < map->GetNumOfTiles_MapWidth() + 1; ++k)
		{
			m = k + (int)tileOffset.x;

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


		if (player->GetWeaponType() == 3)
		{
			Vector3 worldPos(worldX, worldY, 0.f);
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(weaponRot, 0, 0, 1);
			modelStack.Scale(((worldPos - player->pos)).Length() * 2, 3, 10);
			RenderMesh(meshList[GEO_LASER], false);
			modelStack.PopMatrix();
		}
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

		if (player->GetWeaponType() == 3)
		{
			Vector3 worldPos(worldX, worldY, 0.f);
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(weaponRot, 0, 0, 1);
			modelStack.Scale(((worldPos - player->pos)).Length() * 2, 3, 10);
			RenderMesh(meshList[GEO_LASER], false);
			modelStack.PopMatrix();
		}
	}
}

void SP3::RenderUI()
{
	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_HEALTHBACK], 200.f, 5.f, 1.f, 10, 100);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_HEALTH], (float)player->GetPlayerHealth(),5.f,1.f, 10,100);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_OVERHEATBACK], 200.f, 5.f, 1.f, 10, 95);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_OVERHEAT], (float)player->GetWeapon()->GetOverheatBar() * 2, 5.f, 1.f, 10, 95);
	modelStack.PopMatrix();


	if (player->GetElement() == ELEMENTS::NONE)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_WEAPONUI1], 35.f, 15.f, 10.f, 170, 98);
		modelStack.PopMatrix();
	}
	else if (player->GetElement() ==  ELEMENTS::FIRE)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_WEAPONUI2], 35.f, 15.f, 10.f, 170, 98);
		modelStack.PopMatrix();
	}
	else if (player->GetElement() == ELEMENTS::LIGHTNING)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_WEAPONUI3], 35.f, 15.f, 10.f, 170, 98);
		modelStack.PopMatrix();
	}
	else if (player->GetElement() == ELEMENTS::ICE)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_WEAPONUI4], 35.f, 15.f, 10.f, 170, 98);
		modelStack.PopMatrix();
	}
	else if (player->GetElement() == ELEMENTS::LIFESTEAL)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_WEAPONUI5], 35.f, 15.f, 10.f, 170, 98);
		modelStack.PopMatrix();
	}


	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_WEAPONUI1], 87.5f, 10.f, 10.f, 105, 98);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_BULLET1], 5, 5, 5, 70, 98);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_BULLET2], 5, 5, 5, 90, 98);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_BULLET3], 5, 5, 5, 110, 98);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_BULLET4], 5, 5, 5, 130, 98);
	modelStack.PopMatrix();

	switch (player->GetWeaponType())
	{
	case 0:
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_PISTOL],10.f, 10.f, 10.f, 170, 98);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate((float)worldX, (float)worldY, 1);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_CROSSHAIR], false);
		modelStack.PopMatrix();

		break;
	case 1:
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_RIFLE],25.f, 10.f, 10.f, 170, 98);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate((float)worldX, (float)worldY, 1);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_CROSSHAIR], false);
		modelStack.PopMatrix();

		break;
	case 2:
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_SHOTGUN], 25.f, 10.f, 10.f, 170, 98);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate((float)worldX, (float)worldY, 1);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_CROSSHAIR], false);
		modelStack.PopMatrix();

		break;
	case 3:
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_SNIPER], 25.f, 10.f, 10.f, 170, 98);
		modelStack.PopMatrix();

		break;
	}

	std::stringstream text;
	text << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], text.str(), Color(0.f, 1.f, 0.f), 20, 10, 10);

	std::stringstream text2;
	text2 << player->GetPlayerHealth();
	RenderTextOnScreen(meshList[GEO_TEXT], text2.str() + "/200", Color(0.f, 1.f, 0.f), 15, 98, 659);

	std::stringstream text3;
	text3 << (int)player->GetWeapon()->GetOverheatBar();
	RenderTextOnScreen(meshList[GEO_TEXT], text3.str() + "/100", Color(1.f, 1.f, 0.f), 15, 98, 626);

	std::stringstream text4;
	text4 << player->GetElementCount(ELEMENTS::FIRE);
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text4.str(), Color(1.f, 1.f, 1.f), 23, 490, 643);

	std::stringstream text5;
	text5 << player->GetElementCount(ELEMENTS::LIGHTNING);
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text5.str(), Color(1.f, 1.f, 1.f), 23, 625, 643);

	std::stringstream text6;
	text6 << player->GetElementCount(ELEMENTS::ICE);
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text6.str(), Color(1.f, 1.f, 1.f), 23, 755, 643);

	std::stringstream text7;
	text7 << player->GetElementCount(ELEMENTS::LIFESTEAL);
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text7.str(), Color(1.f, 1.f, 1.f), 23, 885, 643);
}

void SP3::RenderParticle()
{
	for (vector<ParticleObject*>::iterator it = ParticleManager::GetInstance().GetList().begin(); it != ParticleManager::GetInstance().GetList().end(); ++it)
	{
		ParticleObject* particle = (ParticleObject *)*it;
		if (particle->active)
		{
			if (particle->type == P_TEXT)
			{
				TextParticle* textParticle = dynamic_cast<TextParticle*>(particle);
				modelStack.PushMatrix();
				modelStack.Translate(textParticle->pos.x, textParticle->pos.y, textParticle->pos.z);
				modelStack.Scale(textParticle->scale.x, textParticle->scale.y, textParticle->scale.z);
				RenderText(meshList[GEO_TEXT], textParticle->text, Color(1.f, 0.f, 0.f));
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.PushMatrix();
				modelStack.Translate(particle->pos.x, particle->pos.y, particle->pos.z);
				modelStack.Scale(particle->scale.x, particle->scale.y, particle->scale.z);
				RenderMesh(particle->mesh);
				modelStack.PopMatrix();
			}
		}
	}
}