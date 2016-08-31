#include "SceneUpgrade.h"
#include "GL\glew.h"
#include "SceneMainMenu.h"
#include "Application.h"
#include "SceneManager.h"
#include <sstream>
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "WeaponStorage.h"

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
	selectedStats = 0;

	statsDisplay = false;
	selectable = true;
	upgradable = false;
}

void SceneUpgrade::Update(double dt)
{
	SceneBase::Update(dt);
	selectWeapon();

	if (statsDisplay == true)
		selectStats();

	Upgrade();
	nextLevel();
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
	RenderArrowWeapons();

	if (statsDisplay == true)
		RenderArrowStats();

	DisplayStats();

	if (upgradable == true)
		DisplayUpgrades();
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

void SceneUpgrade::RenderArrowWeapons()
{
	if (selectable == true)
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
}

void SceneUpgrade::DisplayStats()
{
	std::stringstream text;
	text << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDamage();
	RenderTextOnScreen(meshList[GEO_TEXT], "Damage: " + text.str(), Color(0.f, 0.f, 0.f), 25, 400, 450);

	std::stringstream text2;
	text2 << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDefaultFireRate();
	RenderTextOnScreen(meshList[GEO_TEXT], "Fire Rate: " + text2.str(), Color(0.f, 0.f, 0.f), 25, 400, 400);

	std::stringstream text3;
	text3 << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetOverheatRate();
	RenderTextOnScreen(meshList[GEO_TEXT], "Overheat: " + text3.str(), Color(0.f, 0.f, 0.f), 25, 400, 350);

	std::stringstream text4;
	text4 << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetCoolDownRate();
	RenderTextOnScreen(meshList[GEO_TEXT], "Cooldown: " + text4.str(), Color(0.f, 0.f, 0.f), 25, 400, 300);
}

void SceneUpgrade::RenderArrowStats()
{
	if (selectedStats == 0)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 15, 20, 10, 85, 83);
		modelStack.PopMatrix();
	}

	else if (selectedStats == 1)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 15, 20, 10, 85, 74);
		modelStack.PopMatrix();
	}

	else if (selectedStats == 2)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 15, 20, 10, 85, 65);
		modelStack.PopMatrix();
	}

	else if (selectedStats == 3)
	{
		modelStack.PushMatrix();
		RenderObjOnScreen(meshList[GEO_ARROWPOINTER], 15, 20, 10, 85, 56);
		modelStack.PopMatrix();
	}
}

void SceneUpgrade::DisplayUpgrades()
{
	if (selectedStats == 0)
	{
		std::stringstream text;
		text << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDamage();
		RenderTextOnScreen(meshList[GEO_TEXT], "Damage: " + text.str(), Color(0.f, 0.f, 0.f), 25, 400, 120);

		std::stringstream text2;
		text2 << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDamage() + 20;
		RenderTextOnScreen(meshList[GEO_TEXT], "Damage: " + text2.str(), Color(0.f, 0.f, 1.f), 25, 400, 100);

	}

	else if (selectedStats == 1)
	{
		std::stringstream text;
		text << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDefaultFireRate();
		RenderTextOnScreen(meshList[GEO_TEXT], "Fire Rate: " + text.str(), Color(0.f, 0.f, 0.f), 22, 400, 120);

		std::stringstream text2;
		text2 << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDefaultFireRate() - 0.1f;
		RenderTextOnScreen(meshList[GEO_TEXT], "Fire Rate: " + text2.str(), Color(0.f, 0.f, 1.f), 22, 400, 100);

		if (WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDefaultFireRate() < 0.1f)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Fire Rate: 0.1", Color(0.f, 0.f, 1.f), 22, 400, 100);
		}

	}

	else if (selectedStats == 2)
	{
		std::stringstream text;
		text << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetOverheatRate();
		RenderTextOnScreen(meshList[GEO_TEXT], "Overheat: " + text.str(), Color(0.f, 0.f, 0.f), 25, 400, 120);

		std::stringstream text2;
		text2 << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetOverheatRate() - 2;
		RenderTextOnScreen(meshList[GEO_TEXT], "Overheat: " + text2.str(), Color(0.f, 0.f, 1.f), 25, 400, 100);

		if (WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetOverheatRate() < 2)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Overheat: 1", Color(0.f, 0.f, 1.f), 25, 400, 100);
		}

	}

	else if (selectedStats == 3)
	{
		std::stringstream text;
		text << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetCoolDownRate();
		RenderTextOnScreen(meshList[GEO_TEXT], "Cooldown: " + text.str(), Color(0.f, 0.f, 0.f), 25, 400, 120);

		std::stringstream text2;
		text2 << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetCoolDownRate() + 2;
		RenderTextOnScreen(meshList[GEO_TEXT], "Cooldown: " + text2.str(), Color(0.f, 0.f, 1.f), 25, 400, 100);
	}
}

void SceneUpgrade::selectWeapon()
{
	if (selectable == true)
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

	if (Application::GetInstance().controller->IsKeyPressed(ENTER))
	{
		statsDisplay = true;
		selectable = false;
		upgradable = true;
		/*if (selectedWeapon == 0)
		{
			selectedStats = 0;
		}*/
	}
}

void SceneUpgrade::selectStats()
{
	if (Application::GetInstance().controller->IsKeyPressed(GODOWN) || Application::GetInstance().controller->IsKeyPressed(MOVE_DOWN))
		selectedStats = (selectedStats + 1) % STATS_END;

	if (Application::GetInstance().controller->IsKeyPressed(GOUP) || Application::GetInstance().controller->IsKeyPressed(MOVE_UP))
	{
		selectedStats = (selectedStats - 1) % STATS_END;
		if (selectedStats < 0)
			selectedStats = STATS_END - 1;
	}

	if (Application::GetInstance().controller->IsKeyPressed(EXIT))
	{
		statsDisplay = false;
		selectable = true;
		upgradable = false;
	}


}

void SceneUpgrade::Upgrade()
{
	if (Application::GetInstance().controller->IsKeyPressed(JUMP))
	{
		if (selectedStats == 0)
			WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->setDamage(WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDamage() + 20);

		else if (selectedStats == 1)
		{
			WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->setFireRate(WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->getDefaultFireRate() - 0.1f);
			if (WeaponStorage::GetInstance().GetInstance().GetWeapon()[selectedWeapon]->getDefaultFireRate() < 0.1f)
				WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->setDefaultFireRate(0.1f);
				
		}
		else if (selectedStats == 2)
		{
			WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->setOverheatRate(WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetOverheatRate() - 2);
			if (WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetOverheatRate() < 2)
				WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->setOverheatRate(2);
			std::cout << WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetOverheatRate() << std::endl;

		}
		else if (selectedStats == 3)
		{
			WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->SetCoolDownRate(WeaponStorage::GetInstance().GetWeapon()[selectedWeapon]->GetCoolDownRate() + 2);
		}


	}
}

void SceneUpgrade::nextLevel()
{
	if (Application::GetInstance().controller->IsKeyPressed(MOVE_RIGHT) || Application::GetInstance().controller->IsKeyPressed(GORIGHT))
	{
		SceneManager::GetInstance().ChangeScene("Hell");
	}
}


void SceneUpgrade::Exit()
{
	SceneBase::Exit();
}