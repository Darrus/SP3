#include "SceneCredit.h"
#include "Application.h"
#include "SceneManager.h"
#include <sstream>
#include "SoundEngine.h"


SceneCredit::SceneCredit()
{

}

SceneCredit::~SceneCredit()
{
	Exit();
}

void SceneCredit::Init()
{
	SceneBase::Init();

	Math::InitRNG();

	camera = new Camera();
	camera->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));

	SoundEngine::GetInstance().AddSound("Credit", "Sound//Maplestory_Signal _Medium.mp3", 0.5f);
	SoundEngine::GetInstance().Play("Credit");

	Application::ShowCursor(false);
}

void SceneCredit::Update(double dt)
{
	SceneBase::Update(dt);

	if (Application::GetInstance().controller->IsKeyPressed(ENTER) || Application::GetInstance().controller->IsKeyPressed(EXIT))
		SceneManager::GetInstance().ChangeScene("MainMenu");
}

void SceneCredit::Render()
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

	RenderUI();
}

void SceneCredit::Exit()
{
	SceneBase::Exit();
}

void SceneCredit::RenderUI()
{

	modelStack.PushMatrix();
	modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
	modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
	RenderMesh(meshList[GEO_CREDIT], false);
	modelStack.PopMatrix();
}