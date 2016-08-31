#ifndef SCENEEARTH_H
#define SCENEEARTH_H

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

class SceneEarth : public SceneBase
{
public:
	SceneEarth();
	virtual ~SceneEarth();

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

	bool story;

	float fps;
	float timer;

	double worldX, worldY;
	double mouseX, mouseY;
};

#endif