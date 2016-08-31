#ifndef HELL_BOSS_H
#define HELL_BOSS_H

#include "SceneBase.h"
#include "ParallaxBackground.h"
#include "TileMap.h"
#include "Player.h"
#include "CameraFollow.h"
#include "Pistol.h"
#include "Bullet.h"
#include "Element.h"
#include "Boss.h"

class HellBoss : public SceneBase
{
public:
	HellBoss();
	virtual ~HellBoss();

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
	Weapon* weapon;
	Items* items;
	Boss* boss;
	float timer;

	double worldX, worldY;
	double mouseX, mouseY;
};
#endif