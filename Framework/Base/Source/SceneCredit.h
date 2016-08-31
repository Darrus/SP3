#ifndef SCENECREDIT_H
#define SCENECREDIT_H

#include "SceneBase.h"

using std::vector;

class SceneCredit : public SceneBase
{
public:
	SceneCredit();
	virtual ~SceneCredit();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderUI();
};

#endif