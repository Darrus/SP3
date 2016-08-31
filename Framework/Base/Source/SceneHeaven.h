#ifndef SCENE_HEAVEN_H
#define SCENE_HEAVEN_H

#include "SceneBase.h"
#include "ParallaxBackground.h"
#include "TileMap.h"
#include "Player.h"
#include "CameraFollow.h"
#include "Pistol.h"
#include "Bullet.h"
#include "Element.h"
#include "GoManager.h"

class SceneHeaven : public SceneBase
{
public:
	SceneHeaven();
	virtual ~SceneHeaven();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderWeaponObject(Weapon* go);
	void RenderParticle();
	void RenderUI();

	TileMap* map;
	ParallaxBackground background;
	Player* player;
	CameraFollow* camFollow;
	Items* items;

	bool story;
	float fps;

	double worldX, worldY;
	double mouseX, mouseY;
};

#endif