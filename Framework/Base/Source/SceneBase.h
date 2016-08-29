#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include <vector>
#include "Camera.h"

class SceneBase : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderObjOnScreen(Mesh* mesh, float sizeX, float sizeY,float sizeZ, float x, float y);
	void Render2DMesh(Mesh *mesh, bool enableLight, float size, float x, float y, bool flip);
	void RenderMesh(Mesh *mesh, bool enableLight = false);
	void RenderTile(Mesh *mesh, int id, float x, float y, float size);

protected:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_BALL,
		GEO_CUBE,
		GEO_HEALTH,
		GEO_HEALTHBACK,

		GEO_OVERHEAT,
		GEO_OVERHEATBACK,

		GEO_PISTOL,
		GEO_RIFLE,
		GEO_SHOTGUN,
		GEO_SNIPER,

		GEO_LASER,

		GEO_WEAPONUI1,
		GEO_WEAPONUI2,
		GEO_WEAPONUI3,
		GEO_WEAPONUI4,
		GEO_WEAPONUI5,

		GEO_BULLET1,
		GEO_BULLET2,
		GEO_BULLET3,
		GEO_BULLET4,

		GEO_CROSSHAIR,

		GEO_ITEMSBACK,
		GEO_HEALTHPOTION,
		GEO_SPEEDPOTION,
		GEO_JUMPPOTION,

		GEO_GAMEOVER,
		GEO_STORY,

		GEO_TEXTBOX,
		GEO_MAINMENU,
		GEO_ARROWPOINTER,
		GEO_INSTRUCTIONS1,
		GEO_INSTRUCTIONS2,
		GEO_LEVELEDITOR1,
		GEO_LEVELEDITOR2,

		NUM_GEOMETRY,
	};

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera* camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];

	bool bLightEnabled;

	float m_screenWidth;
	float m_screenHeight;

	float fps;
};

#endif