#ifndef STUDIO_PROJECT_3_H
#define STUDIO_PROJECT_3_H

#include "SceneBase.h"
#include "MapEditor.h"

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
};

#endif