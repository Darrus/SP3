#ifndef SCENEHELL_H
#define SCENEHELL_H

#include <vector>
#include "SceneBase.h"
#include "ParallaxBackground.h"
#include "TileMap.h"
#include "Player.h"
#include "CameraFollow.h"
#include "Pistol.h"
#include "Bullet.h"
#include "Element.h"

using std::vector;

class SceneHell : public SceneBase
{
public:
	SceneHell();
	virtual ~SceneHell();

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

	float fps;

	double worldX, worldY;
	double mouseX, mouseY;
};

#endif