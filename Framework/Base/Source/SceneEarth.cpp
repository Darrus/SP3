#include "SceneEarth.h"
#include "Application.h"
#include "SceneManager.h"
#include <sstream>
#include "EnemyFactory.h"
#include "TextParticle.h"
#include "MeshGenerator.h"
#include "GoManager.h"
#include "ParticleManager.h"
#include "HealthPotions.h"
#include "SoundEngine.h"

SceneEarth::SceneEarth()
{

}

SceneEarth::~SceneEarth()
{
	Exit();
}

void SceneEarth::Init()
{
	SceneBase::Init();

	Math::InitRNG();

	map = new TileMap();
	map->Init(&Application::GetInstance().m_window_height, &Application::GetInstance().m_window_width, 32);
	map->LoadMap("Earth");
	map->LoadTileSheet("Image//tilesheet.tga");

	player = new Player();
	player->Init(map, Vector3(50.f, 200.f, 0.f), Vector3(32.f, 32.f, 1.f));
	player->active = true;
	GoManager::GetInstance().Add(player);

	camFollow = new CameraFollow();
	camFollow->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));
	camFollow->LookAt(player);
	camFollow->SetMap(map);
	camera = camFollow;

	weapon = new Weapon();
	background.Init(&camera->position, 800, 600);

	SoundEngine::GetInstance().GetInstance().AddRepeatSound("BG_Sound", "Sound//MapleStory_Here_Comes.mp3", 0.2f);
	SoundEngine::GetInstance().GetInstance().Play("BG_Sound");

	EnemyFactory::Create("RandomGoblin", Vector3(600.f, 340.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(300.f, 650.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(1000.f, 150.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(1600.f, 150.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(2000.f, 150.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(910.f, 340.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(1540.f, 380.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(1550.f, 500.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(2500.f, 300.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(2870.f, 440.f, 0.f), map);
	EnemyFactory::Create("RandomGoblin", Vector3(2600.f, 730.f, 0.f), map);

	Items *potion = new HealthPotion();
	potion->active = true;
	potion->pos.Set(419.f, 816.f, 0.f);
	GoManager::GetInstance().Add(potion);

	potion = new HealthPotion();
	potion->active = true;
	potion->pos.Set(1147.77f, 624.f, 0.f);
	GoManager::GetInstance().Add(potion);

	potion = new HealthPotion();
	potion->active = true;
	potion->pos.Set(2070.53, 656.f, 0.f);
	GoManager::GetInstance().Add(potion);

	potion = new HealthPotion();
	potion->active = true;
	potion->pos.Set(2298.85f, 800.f, 0.f);
	GoManager::GetInstance().Add(potion);

	potion = new HealthPotion();
	potion->active = true;
	potion->pos.Set(2802.46, 912.f, 0.f);
	GoManager::GetInstance().Add(potion);

	fps = 0.f;

	background.Init(&camera->position, 800, 600);
	background.LoadBackground("Image//EarthRear.tga", Vector3(1980, 1080, 0));
	background.LoadBackground("Image//EarthMid.tga", Vector3(1980, 1080, 0));
	background.LoadBackground("Image//EarthFront.tga", Vector3(1980, 1080, 0));

	story = true;

	timer = 5.f;
}

void SceneEarth::Update(double dt)
{

	SceneBase::Update(dt);

	std::cout << player->pos << std::endl;

	//Get mouse pos in world
	Application::GetInstance().GetMousePos(mouseX, mouseY);
	mouseY = Application::GetInstance().m_window_height - mouseY;
	worldX = mouseX + camera->position.x;
	worldY = mouseY + camera->position.y;
	player->SetMousePos((float)worldX, (float)worldY);

	camera->Update(dt);
	background.Update();
	ParticleManager::GetInstance().Update(dt);
	fps = 1 / (float)dt;


	if (story == true && Application::GetInstance().controller->IsKeyPressed(BACKSPACE))
	{
		story = false;
	}
	else if (story == false)
	{
		GoManager::GetInstance().Update(dt);
	}

	if(GoManager::GetInstance().GetEnemyCount() <= 0)
		timer -= dt;

	if (Application::GetInstance().controller->OnHold(CTRL) && Application::GetInstance().controller->IsKeyPressed(NEXT) || timer < 0.f)
		SceneManager::GetInstance().ChangeScene("EarthBoss");

	if (Application::GetInstance().controller->OnHold(EXIT))
		SceneManager::GetInstance().ChangeScene("MainMenu");

	if (player->GetPlayerHealth() <= 0)
	{
		SceneManager::GetInstance().ChangeScene("GameOver");
	}
}

void SceneEarth::Render()
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

				modelStack.PushMatrix();
				modelStack.Translate(enemy->pos.x - (enemy->scale.x * 0.5), enemy->pos.y + (enemy->scale.y *0.5), enemy->pos.z);
				modelStack.Scale(enemy->scale.x * 4, 15, 1);
				RenderMesh(meshList[GEO_HEALTHBACK], false);
				modelStack.PopMatrix();
				if (((enemy->GetHealth() / enemy->GetMaxHealth())) * 100 >= 76 && ((enemy->GetHealth() / enemy->GetMaxHealth())) * 100 <= 100)
				{
					modelStack.PushMatrix();
					modelStack.Translate(enemy->pos.x - (enemy->scale.x * 0.5), enemy->pos.y + (enemy->scale.y *0.5), enemy->pos.z);
					modelStack.Scale(((enemy->GetHealth() / enemy->GetMaxHealth()) *  enemy->scale.x) * 4, 15, 1);
					RenderMesh(meshList[GEO_HEALTHFRONT01], false);
					modelStack.PopMatrix();
				}
				if (((enemy->GetHealth() / enemy->GetMaxHealth())) * 100 >= 40 && ((enemy->GetHealth() / enemy->GetMaxHealth())) * 100 <= 76)
				{
					modelStack.PushMatrix();
					modelStack.Translate(enemy->pos.x - (enemy->scale.x * 0.5), enemy->pos.y + (enemy->scale.y *0.5), enemy->pos.z);
					modelStack.Scale(((enemy->GetHealth() / enemy->GetMaxHealth()) *  enemy->scale.x) * 4, 15, 1);
					RenderMesh(meshList[GEO_HEALTHFRONT02], false);
					modelStack.PopMatrix();
				}
				if (((enemy->GetHealth() / enemy->GetMaxHealth())) * 100 >= 0 && ((enemy->GetHealth() / enemy->GetMaxHealth())) * 100 <= 40)
				{
					modelStack.PushMatrix();
					modelStack.Translate(enemy->pos.x - (enemy->scale.x * 0.5), enemy->pos.y + (enemy->scale.y *0.5), enemy->pos.z);
					modelStack.Scale(((enemy->GetHealth() / enemy->GetMaxHealth()) *  enemy->scale.x) * 4, 15, 1);
					RenderMesh(meshList[GEO_HEALTHFRONT03], false);
					modelStack.PopMatrix();
				}
			}
		}
	}

	RenderParticle();
	RenderUI();
}

void SceneEarth::Exit()
{
	SceneBase::Exit();
	if (map)
		delete map;
	map = NULL;
	background.ClearBackgrounds();
}

// Renders
void SceneEarth::RenderWeaponObject(Weapon* go)
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
			Vector3 worldPos((float)worldX, (float)worldY, 0.f);
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
			Vector3 worldPos((float)worldX, (float)worldY, 0.f);
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(weaponRot, 0, 0, 1);
			modelStack.Scale(((worldPos - player->pos)).Length() * 2, 3, 10);
			RenderMesh(meshList[GEO_LASER], false);
			modelStack.PopMatrix();
		}
	}
}

void SceneEarth::RenderUI()
{
	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_HEALTHBACK], 200.f, 5.f, 1.f, 10, 100);
	modelStack.PopMatrix();

	if ((float)player->GetPlayerHealth() >= 0.f && (float)player->GetPlayerHealth() <= 50.f)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_HEALTHFRONT03], (float)player->GetPlayerHealth(), 5.f, 1.f, 10, 100);
		modelStack.PopMatrix();
	}
	if ((float)player->GetPlayerHealth() >= 51.f && (float)player->GetPlayerHealth() <= 150.f)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_HEALTHFRONT02], (float)player->GetPlayerHealth(), 5.f, 1.f, 10, 100);
		modelStack.PopMatrix();
	}
	if ((float)player->GetPlayerHealth() >= 151.f && (float)player->GetPlayerHealth() <= 200.f)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_HEALTHFRONT01], (float)player->GetPlayerHealth(), 5.f, 1.f, 10, 100);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_OVERHEATBACK], 200.f, 5.f, 1.f, 10, 95);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_OVERHEAT], (float)player->GetWeapon()->GetOverheatBar() * 2, 5.f, 1.f, 10, 95);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_ITEMSBACK], 10.f, 8.f, 1.f, 15, 89);
	modelStack.PopMatrix();

	if (player->inventory.GetSelectedItem())
	{
		RenderObjOnScreen(player->inventory.GetSelectedItem()->mesh, 10.f, 8.f, 1.f, 15, 89);
	}


	/*else if (items->SPEEDBOOST)
	{
	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_SPEEDPOTION], 10.f, 8.f, 1.f, 15, 89);
	modelStack.PopMatrix();
	}*/
	//else if (items->JUMPBOOST)
	//{
	//	modelStack.PushMatrix();
	//	RenderObjOnScreen(meshList[GEO_JUMPPOTION], 10.f, 8.f, 1.f, 15, 89);
	//	modelStack.PopMatrix();
	//}



	if (player->GetElement() == ELEMENTS::NONE)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_WEAPONUI1], 35.f, 15.f, 10.f, 170, 98);
		modelStack.PopMatrix();
	}
	else if (player->GetElement() == ELEMENTS::FIRE)
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
	RenderObjOnScreen(meshList[GEO_WEAPONUI1], 87.5f, 8.f, 10.f, 105, 98);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_BULLET1], 5, 4, 5, 70, 98);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_BULLET2], 5, 4, 5, 90, 98);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_BULLET3], 5, 4, 5, 110, 98);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_BULLET4], 5, 4, 5, 130, 98);
	modelStack.PopMatrix();


	switch (player->GetWeaponType())
	{
	case 0:
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_PISTOL], 10.f, 10.f, 10.f, 170, 98);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate((float)worldX, (float)worldY, 1);
		modelStack.Scale(50, 50, 50);
		RenderMesh(meshList[GEO_CROSSHAIR], false);
		modelStack.PopMatrix();

		break;
	case 1:
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_RIFLE], 25.f, 10.f, 10.f, 170, 98);
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

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_COIN], 10, 8, 10, 15, 80);
	modelStack.PopMatrix();

	std::stringstream text;
	text << player->getCoinAmount();
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text.str(), Color(1.f, 1.f, 1.f), 15, 85, 440);

	text.str("");
	text << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], text.str(), Color(0.f, 1.f, 0.f), 20, 10, 10);

	std::stringstream text2;
	text2 << player->GetPlayerHealth();
	RenderTextOnScreen(meshList[GEO_TEXT], text2.str() + "/200", Color(0.f, 1.f, 0.f), 15, 60, 547);

	std::stringstream text3;
	text3 << (int)player->GetWeapon()->GetOverheatBar();
	RenderTextOnScreen(meshList[GEO_TEXT], text3.str() + "/100", Color(1.f, 1.f, 0.f), 15, 60, 520);

	std::stringstream text4;
	text4 << player->GetElementCount(ELEMENTS::FIRE);
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text4.str(), Color(1.f, 1.f, 1.f), 15, 305, 538);

	std::stringstream text5;
	text5 << player->GetElementCount(ELEMENTS::LIGHTNING);
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text5.str(), Color(1.f, 1.f, 1.f), 15, 390, 538);

	std::stringstream text6;
	text6 << player->GetElementCount(ELEMENTS::ICE);
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text6.str(), Color(1.f, 1.f, 1.f), 15, 475, 538);

	std::stringstream text7;
	text7 << player->GetElementCount(ELEMENTS::LIFESTEAL);
	RenderTextOnScreen(meshList[GEO_TEXT], "X" + text7.str(), Color(1.f, 1.f, 1.f), 15, 555, 538);

	if (story == true)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_STORY], 180.f, 100.f, 50.f, 97, 54);
		modelStack.PopMatrix();
	}
}

void SceneEarth::RenderParticle()
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