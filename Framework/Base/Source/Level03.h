#ifndef LEVEL03_H
#define LEVEL03_H

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

class Level03 : public SceneBase
{
public:
	Level03();
	virtual ~Level03();

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

	bool story;

	float fps;

	double worldX, worldY;
	double mouseX, mouseY;
};

#endif