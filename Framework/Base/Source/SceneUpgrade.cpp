#include "SceneUpgrade.h"
#include "GL\glew.h"
#include "SceneMainMenu.h"
#include "Application.h"
#include "SceneManager.h"
#include <sstream>
#include "MeshBuilder.h"
#include "LoadTGA.h"

SceneUpgrade::SceneUpgrade()
{

}

SceneUpgrade::~SceneUpgrade()
{
	Exit();
}

void SceneUpgrade::Init()
{
	SceneBase::Init();

	camera = new Camera();
	camera->Init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));

	meshList[GEO_ARROWPOINTER] = MeshBuilder::GenerateQuad("arrowPointer", Color(1, 1, 1), 1.f);
	meshList[GEO_ARROWPOINTER]->textureArray[0] = LoadTGA("Image//arrowPointer.tga");

	meshList[GEO_UPGRADEMENU] = MeshBuilder::GenerateQuad("UpgradeMenu", Color(1, 1, 1), 1.f);
	meshList[GEO_UPGRADEMENU]->textureArray[0] = LoadTGA("Image//UpgradeMenu.tga");

	selectedWeapon = 0;
}

void SceneUpgrade::Update(double dt)
{
	SceneBase::Update(dt);
	selectWeapon();
}

void SceneUpgrade::Render()
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

	modelStack.PushMatrix();
	modelStack.Translate(Application::GetInstance().m_window_width * 0.5, Application::GetInstance().m_window_height * 0.5, 0);
	modelStack.Scale(Application::GetInstance().m_window_width, Application::GetInstance().m_window_height, 1);
	RenderMesh(meshList[GEO_UPGRADEMENU], false);
	modelStack.PopMatrix();

	DisplayWeapons();
	RenderArrow();
	DisplayUpgradePistol();
}

void SceneUpgrade::DisplayWeapons()
{
	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_PISTOL], 20.f, 20.f, 10.f, 40, 83);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_RIFLE], 40.f, 20.f, 10.f, 40, 65);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_SHOTGUN], 40.f, 15.f, 10.f, 40, 45);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderObjOnScreen(meshList[GEO_SNIPER], 40.f, 15.f, 10.f, 40, 25);
	modelStack.PopMatrix();
}

void SceneUpgrade::RenderArrow()
{
	if (selectedWeapon == 0)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 15, 20, 10, 10, 83);
		modelStack.PopMatrix();
	}

	else if (selectedWeapon == 1)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 15, 20, 10, 10, 68);
		modelStack.PopMatrix();
	}

	if (selectedWeapon == 2)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 15, 20, 10, 10, 45);
		modelStack.PopMatrix();
	}

	if (selectedWeapon == 3)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 15, 20, 10, 10, 25);
		modelStack.PopMatrix();
	}
}

void SceneUpgrade::DisplayUpgradePistol()
{
	
	//std::stringstream text;
	//text << weapon->getDamage();
	
	{
		std::stringstream text;
		text << weapon->getDamage();
		RenderTextOnScreen(meshList[GEO_TEXT], "Damage: " + text.str(), Color(0.f, 0.f, 0.f), 25, 400, 450);

		RenderTextOnScreen(meshList[GEO_TEXT], "Fire Rate: " /*+ text.str()*/, Color(0.f, 0.f, 0.f), 25, 400, 400);

		RenderTextOnScreen(meshList[GEO_TEXT], "Overheat: " /*+ text.str()*/, Color(0.f, 0.f, 0.f), 25, 400, 350);

		RenderTextOnScreen(meshList[GEO_TEXT], "Cooldown: " /*+ text.str()*/, Color(0.f, 0.f, 0.f), 25, 400, 300);
	}
}

void SceneUpgrade::selectWeapon()
{
	if (Application::GetInstance().controller->IsKeyPressed(GODOWN) || Application::GetInstance().controller->IsKeyPressed(MOVE_DOWN))
		selectedWeapon = (selectedWeapon + 1) % DISPLAY_END;

	if (Application::GetInstance().controller->IsKeyPressed(GOUP) || Application::GetInstance().controller->IsKeyPressed(MOVE_UP))
	{
		selectedWeapon = (selectedWeapon - 1) % DISPLAY_END;
		if (selectedWeapon < 0)
			selectedWeapon = DISPLAY_END - 1;
	}
}

void SceneUpgrade::Exit()
{
	SceneBase::Exit();
}