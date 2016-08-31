#include "IceGolem.h"
#include "BossSkill.h"
#include "GoManager.h"
#include "MeshGenerator.h"
#include "EnemyIdle.h"

IceGolem::IceGolem()
{
	status.AddImmune("Slow");
	maxHealth = 5000;
	health = maxHealth;
	attackRange = 100.f;
	alertRange = 1000.f;
	patrolRange = 1000.f;
	speed = 50;
	defaultSpeed = 50;
	timeBetweenAttack = 5.f;
	attackCooldown = 0.f;
	attackDamage = 30.f;
	mesh = MeshGenerator::GetInstance().GenerateSprite("Ice Golem", "Image//IceGolem.tga", 4, 8);
	animWalk.Set(8, 11, 1.f, true, 1, true);
	animAttack.Set(16, 23, 1.f, true);
	animDeath.Set(24, 30, 1.f, true);
	chaseDuration = 10.f;
	chaseTimer = chaseDuration;

	if (!state)
	{
		state = new EnemyIdle();
		state->Enter(this, NULL);
	}
}

IceGolem::~IceGolem()
{

}

void IceGolem::Skill()
{
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(mesh);
	static bool skill = false;
	if (sprite->m_currentFrame == 19 && !skill)
	{
		for (int i = 1; i < 10; ++i)
		{
			attackCooldown = timeBetweenAttack;
			BossSkill* skill = new BossSkill();
			skill->active = true;
			Animation anim;
			anim.Set(0, 7, 2.f, true);
			skill->Init(Vector3(100.f * i, 90.f, 1.f), Vector3(64.f, 128.f, 1.f), 50);
			skill->SetSprite("Image//Icicle.tga", 1, 7, anim);
			skill->attackOnFrame = 3;
			GoManager::GetInstance().Add(skill);
		}
		skill = true;
	}
	else if (sprite->m_anim->ended)
	{
		delete state;
		state = new EnemyIdle();
		state->Enter(this, NULL);
		skill = false;
	}
}