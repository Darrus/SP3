#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Mesh.h"
#include "MyMath.h"

struct Animation
{
	Animation(){}

	void Set(int startFrame, int endFrame, float time, bool active, int repeat = 0, bool unlimitedRepeat = false)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->repeatCount = repeat;
		this->animTime = time;
		this->animActive = active;
		this->unlimited = unlimitedRepeat;
	}

	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool unlimited;
	bool ended;
	bool animActive;
};


class SpriteAnimation : public Mesh
{
public:
	SpriteAnimation(const std::string &meshName, int row, int col);
	virtual ~SpriteAnimation();

	void Update(double dt);
	void SetAnimation(int start, int end, float animTime, int repeat = 0, bool unlimited = false);
	void SetAnimation(Animation anim);
	virtual void Render();

	int m_row;
	int m_col;

	float m_currentTime;
	int m_currentFrame;
	int m_playCount;

	Animation *m_anim;
};

#endif