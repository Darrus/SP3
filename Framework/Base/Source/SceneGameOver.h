#ifndef SCENEGAMEOVER_H
#define SCENEGAMEOVER_H

#include "SceneBase.h"

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
	void RenderUI();
};

#endif