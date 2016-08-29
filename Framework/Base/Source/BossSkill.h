#ifndef BOSS_SKILL_H
#define BOSS_SKILL_H

#include <string>

#include "GameObject.h"
#include "AABB_2D.h"
#include "SpriteAnimation.h"

using std::string;

class BossSkill : public GameObject
{
public:
	BossSkill();
	virtual ~BossSkill();

	virtual void Init(Vector3 pos, Vector3 scale, int damage);
	virtual void Update(double dt);
	virtual void HandleInteraction(GameObject* go, double dt);

	void SetSprite(string fileLoc, int row, int col, Animation anim);

	AABB_2D collider;
	SpriteAnimation* sprite;
	int attackOnFrame;
	int damage;
	bool hit;
};

#endif