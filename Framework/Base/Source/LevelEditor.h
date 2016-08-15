#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H

#include "SceneBase.h"
#include "MapEditor.h"

class LevelEditor : public SceneBase
{
public:
	LevelEditor();
	virtual ~LevelEditor();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderEditor();

	MapEditor* editor;
};

#endif