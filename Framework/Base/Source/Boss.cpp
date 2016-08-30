#include "Boss.h"
#include "BossSkill.h"
#include "MeshGenerator.h"
#include "GoManager.h"
#include "EnemyIdle.h"
#include "EnemyAttack.h"
#include "EnemySkill.h"
#include "EnemyChase.h"
#include "EnemyStun.h"
#include "EnemyDeath.h"

Boss::Boss()
{
	status.AddImmune("Slow");
	maxHealth = 5000;
	health = maxHealth;
	attackRange = 140.f;
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
}

Boss::~Boss()
{

}

void Boss::Update(double dt)
{
	status.Update(dt);

	attackCooldown -= dt;

	if (state)
		state->Update(dt);

	collidedWall = false;

	SpriteAnimation* sprite = dynamic_cast<SpriteAnimation*>(mesh);
	if (sprite)
		sprite->Update(dt);

	if (!isGrounded)
		vel.y -= 9.8;

	MapCollision(dt);

	if (health <= 0 && active)
	{
		if (state->GetState() != EnemyStates::ENEMY_DEATH)
		{
			delete state;
			state = new EnemyDeath();
			state->Enter(this, NULL);
		}
	}

	collider.Update();
}

void Boss::Attack(Player* player)
{
	attackCooldown = timeBetweenAttack;
	player->TakeDamage(attackDamage);

	if (pos.x > player->pos.x)
	{
		player->vel.x -= 100;
		player->vel.y += 200;
	}
	else if (pos.x < player->pos.x)
	{
		player->vel.x += 100;
		player->vel.y += 200;
	}

	delete state;
	state = new EnemyIdle();
	state->Enter(this, NULL);
}

void Boss::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (player)
	{
		float dist = (player->pos - pos).LengthSquared();
		if (!state)
		{
			state = new EnemyIdle();
			state->Enter(this, NULL);
		}

		switch (state->GetState())
		{
		case EnemyStates::ENEMY_IDLE:
			if (attackCooldown < 0)
			{
				attackCooldown = timeBetweenAttack;
				ATTACK_DECISION decision = (ATTACK_DECISION)Math::RandIntMinMax((int)ATTACK, (int)SKILL);
				switch (decision)
				{
				case ATTACK:
					delete state;
					state = new EnemyChase();
					state->Enter(this, player);
					break;
				case SKILL:
					delete state;
					state = new EnemySkill();
					state->Enter(this, player);
					break;
				}
			}
			break;
		case EnemyStates::ENEMY_CHASE:
			if (dist < attackRange * attackRange)
			{
				delete state;
				state = new EnemyAttack();
				state->Enter(this, player);
			}
			else if (chaseTimer < 0.f)
			{
				delete state;
				state = new EnemyIdle();
				state->Enter(this, NULL);
			}
			break;
		case EnemyStates::ENEMY_STUN:
			EnemyStun* stun = dynamic_cast<EnemyStun*>(state);
			if (stun && stun->end)
			{
				delete state;
				state = new EnemyIdle();
				state->Enter(this, NULL);
			}
			break;
		}
	}
}

void Boss::MapCollision(double dt)
{
	// Updates position
	newPos = pos + vel * (float)dt;

	// Init Variables
	int tileSize = map->GetTileSize();
	int currentX, currentY, checkUp, checkDown, checkX, checkY;
	currentX = currentY = checkDown = checkUp = checkX = checkY = 0;

	// Make sure object doesnt move out of screen
	if (newPos.x - scale.x * 0.5f <= 0 || newPos.x + scale.x * 0.5f >= map->GetMapWidth())
	{
		collidedWall = true;
		newPos.x = pos.x;
	}

	if (newPos.y - scale.y * 0.5f <= 0 || newPos.y + scale.y * 0.5f >= map->GetMapHeight())
		newPos.y = pos.y;

	// Get Current Tile
	currentX = newPos.x / tileSize;
	currentY = newPos.y / tileSize;

	// Check which direction is the player moving in the X axis
	float dir = 0;
	dir = newPos.x - pos.x;

	// Checks next tile according to player's scale
	checkUp = (newPos.y + scale.y * 0.5f - 1) / tileSize;
	checkDown = (newPos.y - scale.y * 0.5f + 1) / tileSize;

	if (isGrounded) // If enemy is grounded
	{
		// Checks the tile below enemy
		if (map->collisionMap[checkDown - 1][checkX] != 1)
		{
			isGrounded = false;
			collidedWall = true;
		}
	}
	else if (!isGrounded) // If enemy is in the air
	{
		// Checks Down
		if (map->collisionMap[checkDown][currentX] == 1)
		{
			isGrounded = true;
			newPos.y = checkDown * tileSize + scale.y * 0.5f + tileSize;
			vel.y = 0.f;
		}
	}

	pos = newPos;
}

void Boss::Skill()
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