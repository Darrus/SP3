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

	TileMap* map;
	ParallaxBackground background;
	Player* player;
	CameraFollow* camFollow;

	Pistol pistol;
	Bullet* bullet;

	float bulletRate;

	float fps;
};

#endif