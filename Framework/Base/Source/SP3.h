#ifndef STUDIO_PROJECT_3_H
#define STUDIO_PROJECT_3_H

#include "SceneBase.h"
#include "ParallaxBackground.h"
#include "TileMap.h"
#include "Player.h"
#include "CameraFollow.h"
#include "MeleeEnemy.h"

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
	MeleeEnemy* enemy;

	float fps;
};

#endif