#include "EarthGolem.h"
#include "MeshGenerator.h"
#include "EnemyIdle.h"
#include "BossSkill.h"
#include "EnemyBullet.h"
#include "BulletFactory.h"

EarthGolem::EarthGolem()
{
	status.AddImmune("Stun");
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
	mesh = MeshGenerator::GetInstance().GenerateSprite("Earth Golem", "Image//EarthGolem.tga", 4, 10);
	animWalk.Set(10, 13, 1.f, true, 1, true);
	animAttack.Set(20, 29, 1.f, true);
	animDeath.Set(30, 36, 1.f, true);
	chaseDuration = 10.f;
	chaseTimer = chaseDuration;

	if (!state)
	{
		state = new EnemyIdle();
		state->Enter(this, NULL);
	}
}

EarthGolem::~EarthGolem()
{

}

void EarthGolem::Skill()
{
	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(mesh);
	static bool skill = false;
	if (sprite->m_currentFrame == 26 && !skill)
	{
		for (int i = 0; i < 15; ++i)
		{
			attackCooldown = timeBetweenAttack;
			Bullet* bullet = BulletFactory::CreateEnemyBullet("Image//rock.tga", map);
			float spawn = Math::RandFloatMinMax(0.f, 1000.f);
			bullet->pos.Set(spawn, 800.f, 0.f);
			bullet->scale.Set(64.f, 64.f, 1.f);
			bullet->bulletSpeed = 0.f;
			bullet->damage = 50.f;
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