#ifndef STUDIO_PROJECT_3_H
#define STUDIO_PROJECT_3_H

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

class SP3 : public SceneBase
{
public:
	SP3();
	virtual ~SP3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMap(TileMap* map);
	void RenderObject(GameObject* go);
	void RenderWeaponObject(GameObject * go);
	void RenderUI();

	TileMap* map;
	ParallaxBackground background;
	Player* player;
	CameraFollow* camFollow;
	Weapon* weapon;

	float fps;

	double worldX, worldY;
	double mouseX, mouseY;
};

#endif