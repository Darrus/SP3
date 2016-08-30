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
#include "Boss.h"

class HeavenBoss : public SceneBase
{
public:
	HeavenBoss();
	virtual ~HeavenBoss();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderWeaponObject(GameObject * go);
	void RenderParticle();
	void RenderUI();

	TileMap* map;
	ParallaxBackground background;
	Player* player;
	CameraFollow* camFollow;
	Weapon* weapon;
	Items* items;
	Boss* boss;

	double worldX, worldY;
	double mouseX, mouseY;
};
#endif