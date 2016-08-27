#include "SceneGameOver.h"
#include "Application.h"
#include "SceneManager.h"
#include <sstream>
#include "EnemyFactory.h"
#include "TextParticle.h"
#include "MeshGenerator.h"
#include "GoManager.h"
#include "ParticleManager.h"
#include "SoundEngine.h"



SceneGameOver::SceneGameOver()
{

}

SceneGameOver::~SceneGameOver()
{
	Exit();
}

void SceneGameOver::Init()
{
	SceneBase::Init();

	Math::InitRNG();

	map = new TileMap();
	map->Init(&Application::GetInstance().m_window_height, &Application::GetInstance().m_window_width, 32);
	map->LoadMap("Level01");
	map->LoadTileSheet("Image//tilesheet.tga");

	camera = new Camera();
	camera->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));
	background.Init(&camera->position,800,600);

	SoundEngine::GetInstance().AddSound("GameOver", "Sound//GameOver.mp3", 0.5f);
	SoundEngine::GetInstance().Play("GameOver");

	fps = 0.f;
}

void SceneGameOver::Update(double dt)
{
	SceneBase::Update(dt);
	//std::cout << player->pos.x << " " << player->pos.y << std::endl;


	//Get mouse pos in world
	Application::GetInstance().GetMousePos(mouseX, mouseY);
	mouseY = m_screenHeight - mouseY;
	worldX = mouseX + camera->position.x;
	worldY = mouseY + camera->position.y;

	camera->Update(dt);
	GoManager::GetInstance().Update(dt);
	ParticleManager::GetInstance().Update(dt);
	fps = 1 / (float)dt;

	if (Application::GetInstance().controller->OnHold(CTRL) && Application::GetInstance().controller->IsKeyPressed(NEXT))
		SceneManager::GetInstance().ChangeScene("SP3");
}

void SceneGameOver::Render()
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


	RenderParticle();
	RenderUI();
}

void SceneGameOver::Exit()
{
	SceneBase::Exit();
	if (map)
		delete map;
	map = NULL;
	background.ClearBackgrounds();
}




void SceneGameOver::RenderUI()
{

	modelStack.PushMatrix();
	modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
	modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
	RenderMesh(meshList[GEO_GAMEOVER],false);
	modelStack.PopMatrix();
}

void SceneGameOver::RenderParticle()
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