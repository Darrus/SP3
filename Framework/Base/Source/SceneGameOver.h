#ifndef SCENEGAMEOVER_H
#define SCENEGAMEOVER_H

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

class SceneGameOver : public SceneBase
{
public:
	SceneGameOver();
	virtual ~SceneGameOver();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
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