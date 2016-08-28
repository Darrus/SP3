#include "SceneGameOver.h"
#include "Application.h"
#include "SceneManager.h"
#include <sstream>
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

	camera = new Camera();
	camera->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));

	SoundEngine::GetInstance().AddSound("GameOver", "Sound//GameOver.mp3", 0.5f);
	SoundEngine::GetInstance().Play("GameOver");
}

void SceneGameOver::Update(double dt)
{
	SceneBase::Update(dt);

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

	RenderUI();
}

void SceneGameOver::Exit()
{
	SceneBase::Exit();
}

void SceneGameOver::RenderUI()
{

	modelStack.PushMatrix();
	modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
	modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
	RenderMesh(meshList[GEO_GAMEOVER], false);
	modelStack.PopMatrix();
}