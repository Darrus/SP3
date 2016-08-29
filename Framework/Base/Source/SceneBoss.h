#ifndef SCENE_BOSS_H
#define SCENE_BOSS_H

#include "SceneBase.h"
#include "ParallaxBackground.h"
#include "TileMap.h"
#include "Player.h"
#include "CameraFollow.h"
#include "Pistol.h"
#include "Bullet.h"
#include "Element.h"

class SceneBoss : public SceneBase
{
public:
	SceneBoss();
	virtual ~SceneBoss();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMap(TileMap* map);
	void RenderObject(GameObject* go);
	void RenderWeaponObject(GameObject * go);
	void RenderParticle();
	void RenderUI();

	TileMap* map;
	ParallaxBackground background;
	Player* player;
	CameraFollow* camFollow;
	Weapon* weapon;
	Items* items;

	double worldX, worldY;
	double mouseX, mouseY;
};
#endif