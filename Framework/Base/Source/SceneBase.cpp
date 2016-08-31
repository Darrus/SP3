#include "SceneBase.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include <sstream>
#include "LoadTGA.h"
#include "MeshGenerator.h"
#include "GoManager.h"
#include "ParticleManager.h"
#include "SoundEngine.h"
#include "CameraFollow.h"


SceneBase::SceneBase() :
camera(NULL)
{
}

SceneBase::~SceneBase()
{
	Exit();
}

void SceneBase::Init()
{
	// Black background
	glClearColor(0.f, 0.f, 0.4f, 0.f);

	//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS); 

	m_screenHeight = Application::GetWindowHeight();
	m_screenWidth = Application::GetWindowWidth();
	
	glDisable(GL_CULL_FACE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//comg.vertexshader", "Shader//comg.fragmentshader" );
	
	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	
	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);
	
	glUniform1i(m_parameters[U_NUMLIGHTS], 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	//camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0, 1, 0), 1.f);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureArray[0] = LoadTGA("Image//pixel.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[GEO_HEALTHFRONT01] = MeshBuilder::GenerateQuad("HealthBar",Color(1,1,1),0.5f);
	meshList[GEO_HEALTHFRONT01]->textureArray[0] = LoadTGA("Image//healthBarFront01.tga");

	meshList[GEO_HEALTHFRONT02] = MeshBuilder::GenerateQuad("HealthBar", Color(1, 1, 1), 0.5f);
	meshList[GEO_HEALTHFRONT02]->textureArray[0] = LoadTGA("Image//healthBarFront02.tga");

	meshList[GEO_HEALTHFRONT03] = MeshBuilder::GenerateQuad("HealthBar", Color(1, 1, 1), 0.5f);
	meshList[GEO_HEALTHFRONT03]->textureArray[0] = LoadTGA("Image//healthBarFront03.tga");

	meshList[GEO_HEALTHBACK] = MeshBuilder::GenerateQuad("HealthBar", Color(1, 1, 1), 0.5f);
	meshList[GEO_HEALTHBACK]->textureArray[0] = LoadTGA("Image//healthBarBacK.tga");

	meshList[GEO_OVERHEAT] = MeshBuilder::GenerateQuad("OverHeat", Color(1, 1, 1), 0.5f);
	meshList[GEO_OVERHEAT]->textureArray[0] = LoadTGA("Image//OverHeatBarFront.tga");

	meshList[GEO_OVERHEATBACK] = MeshBuilder::GenerateQuad("OverHeatBack", Color(1, 1, 1), 0.5f);
	meshList[GEO_OVERHEATBACK]->textureArray[0] = LoadTGA("Image//OverHeatBarBack.tga");

	meshList[GEO_PISTOL] = MeshBuilder::GenerateQuad("Pistol", Color(1, 1, 1), 1.f);
	meshList[GEO_PISTOL]->textureArray[0] = LoadTGA("Image//Pistol.tga");

	meshList[GEO_RIFLE] = MeshBuilder::GenerateQuad("Rifle", Color(1, 1, 1), 1.f);
	meshList[GEO_RIFLE]->textureArray[0] = LoadTGA("Image//Rifle.tga");

	meshList[GEO_LASER] = MeshBuilder::GenerateQuad("Laser", Color(1, 0, 0), 1.f);
	meshList[GEO_LASER]->textureArray[0] = LoadTGA("Image//Laser.tga");

	meshList[GEO_SHOTGUN] = MeshBuilder::GenerateQuad("Shotgun", Color(1, 1, 1), 1.f);
	meshList[GEO_SHOTGUN]->textureArray[0] = LoadTGA("Image//Shotgun.tga");

	meshList[GEO_SNIPER] = MeshBuilder::GenerateQuad("Sniper", Color(1, 1, 1), 1.f);
	meshList[GEO_SNIPER]->textureArray[0] = LoadTGA("Image//Sniper.tga");

	meshList[GEO_WEAPONUI1] = MeshBuilder::GenerateQuad("UI", Color(1, 1, 1), 1.f);
	meshList[GEO_WEAPONUI1]->textureArray[0] = LoadTGA("Image//WeaponUINormal.tga");

	meshList[GEO_WEAPONUI2] = MeshBuilder::GenerateQuad("UI", Color(1, 1, 1), 1.f);
	meshList[GEO_WEAPONUI2]->textureArray[0] = LoadTGA("Image//WeaponUIFire.tga");

	meshList[GEO_WEAPONUI3] = MeshBuilder::GenerateQuad("UI", Color(1, 1, 1), 1.f);
	meshList[GEO_WEAPONUI3]->textureArray[0] = LoadTGA("Image//WeaponUILightning.tga");

	meshList[GEO_WEAPONUI4] = MeshBuilder::GenerateQuad("UI", Color(1, 1, 1), 1.f);
	meshList[GEO_WEAPONUI4]->textureArray[0] = LoadTGA("Image//WeaponUIIce.tga");

	meshList[GEO_WEAPONUI5] = MeshBuilder::GenerateQuad("UI", Color(1, 1, 1), 1.f);
	meshList[GEO_WEAPONUI5]->textureArray[0] = LoadTGA("Image//WeaponUILifeSteal.tga");

	meshList[GEO_BULLET1] = MeshBuilder::GenerateQuad("Bullet", Color(1, 1, 1), 1.5f);
	meshList[GEO_BULLET1]->textureArray[0] = LoadTGA("Image//FireBall.tga");

	meshList[GEO_BULLET2] = MeshBuilder::GenerateQuad("Bullet", Color(1, 1, 1), 1.5f);
	meshList[GEO_BULLET2]->textureArray[0] = LoadTGA("Image//LightningBall.tga");

	meshList[GEO_BULLET3] = MeshBuilder::GenerateQuad("Bullet", Color(1, 1, 1), 1.f);
	meshList[GEO_BULLET3]->textureArray[0] = LoadTGA("Image//IceBall.tga");

	meshList[GEO_BULLET4] = MeshBuilder::GenerateQuad("Bullet", Color(1, 1, 1), 1.f);
	meshList[GEO_BULLET4]->textureArray[0] = LoadTGA("Image//LifeStealBall.tga");

	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("GEO_CROSSHAIR", Color(1, 1, 1), 1.f);
	meshList[GEO_CROSSHAIR]->textureArray[0] = LoadTGA("Image//CrossHair.tga");

	meshList[GEO_ITEMSBACK] = MeshBuilder::GenerateQuad("Back Quad for Item UI", Color(1, 1, 1), 1.f);
	meshList[GEO_ITEMSBACK]->textureArray[0] = LoadTGA("Image//ItemsBack.tga");

	meshList[GEO_HEALTHPOTION] = MeshBuilder::GenerateQuad("Health Potion", Color(1, 1, 1), 1.f);
	meshList[GEO_HEALTHPOTION]->textureArray[0] = LoadTGA("Image//healthPotion.tga");

	meshList[GEO_SPEEDPOTION] = MeshBuilder::GenerateQuad("Speed Potion", Color(1, 1, 1), 1.f);
	meshList[GEO_SPEEDPOTION]->textureArray[0] = LoadTGA("Image//SpeedPotion.tga");

	meshList[GEO_JUMPPOTION] = MeshBuilder::GenerateQuad("Jump Potion", Color(1, 1, 1), 1.f);
	meshList[GEO_JUMPPOTION]->textureArray[0] = LoadTGA("Image//JumpPotion.tga");

	meshList[GEO_GAMEOVER] = MeshBuilder::GenerateQuad("GameOver", Color(1, 1, 1), 1.f);
	meshList[GEO_GAMEOVER]->textureArray[0] = LoadTGA("Image//GameOver.tga");

	meshList[GEO_CREDIT] = MeshBuilder::GenerateQuad("Credit", Color(1, 1, 1), 1.f);
	meshList[GEO_CREDIT]->textureArray[0] = LoadTGA("Image//Credit.tga");


	meshList[GEO_STORY] = MeshBuilder::GenerateQuad("Story", Color(1, 1, 1), 1.f);
	meshList[GEO_STORY]->textureArray[0] = LoadTGA("Image//Story.tga");

	meshList[GEO_COIN] = MeshBuilder::GenerateSpriteAnimation("Coin",8,8);
	meshList[GEO_COIN]->textureArray[0] = LoadTGA("Image//Coin.tga");

	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_COIN]);
	if (sprite)
	{
		Animation anim;
		anim.Set(0, 63, 1.f, true, 1, true);
		sprite->SetAnimation(anim);
	}

	meshList[GEO_TEXTBOX] = MeshBuilder::GenerateQuad("Textbox", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_TEXTBOX]->textureArray[0] = LoadTGA("Image//textbox.tga");

	bLightEnabled = false;
}

void SceneBase::Update(double dt)
{
	//Keyboard Section

	//
	//if(Application::IsKeyPressed('1'))
	//	glEnable(GL_CULL_FACE);
	//if(Application::IsKeyPressed('2'))
	//	glDisable(GL_CULL_FACE);
	//if(Application::IsKeyPressed('3'))
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//if(Application::IsKeyPressed('4'))
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_COIN]);
	if (sprite)
		sprite->Update(dt);

	fps = (float)(1.f / dt);
}

void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureArray[0] <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureArray[0] <= 0)
		return;

	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	//ortho.SetToOrtho(0, 100, 0, 100, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

void SceneBase::RenderObjOnScreen(Mesh* mesh, float sizeX , float sizeY ,float sizeZ, float x, float y)
{
	if (!mesh || mesh->textureArray[0] <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 192, 0, 108, -10, 10);
	//ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizeX, sizeY, sizeZ);
	RenderMesh(mesh, false);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glDisable(GL_DEPTH_TEST);
}

void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);


	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);

		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}



	for (int i = 0; i < Mesh::MAX_TEXTURES; ++i)
	{
		if (mesh->textureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}

	mesh->Render();
}

void SceneBase::Render2DMesh(Mesh *mesh, bool enableLight, float size, float x, float y, bool flip)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	for (int i = 0; i < Mesh::MAX_TEXTURES; ++i)
	{
		if (mesh->textureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render();
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

void SceneBase::RenderTile(Mesh *mesh, int id, float x, float y, float size)
{
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.Translate(x, y, 0.f);
	modelStack.Scale(size, size, 1.f);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	for (int i = 0; i < Mesh::MAX_TEXTURES; ++i)
	{
		if (mesh->textureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render(id * 6, 6);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
}

void SceneBase::RenderMap(TileMap* map)
{
	int tileSize = map->GetTileSize();
	CameraFollow* follow = dynamic_cast<CameraFollow*>(camera);
	if (follow)
	{
		Vector2 tileOffset = follow->GetTileOffset();
		Vector2 fineOffset = follow->GetFineOffset();

		int m, n;
		for (int i = 0; i < map->GetNumOfTiles_ScreenHeight() + 1; ++i)
		{
			n = i + (int)tileOffset.y;

			if (n >= map->GetNumOfTiles_MapHeight())
				break;

			for (int k = 0; k < map->GetNumOfTiles_ScreenWidth() + 1; ++k)
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
}

void SceneBase::RenderObject(GameObject* go)
{
	modelStack.PushMatrix();
	modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
	if (go->view.x < 0)
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
	modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
	RenderMesh(go->mesh);
	modelStack.PopMatrix();
}

void SceneBase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneBase::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = NULL;
		}
	}

	if (camera)
		delete camera;
	camera = NULL;

	MeshGenerator::GetInstance().ClearMeshGenerator();
	GoManager::GetInstance().ClearList();
	ParticleManager::GetInstance().ClearList();
	SoundEngine::GetInstance().ClearSounds();

	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
