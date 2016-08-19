#include "MeleeEnemy.h"
#include "EnemyIdle.h"
#include "MeshGenerator.h"

MeleeEnemy::MeleeEnemy() :
state(NULL)
{
	sprite = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
	mesh = sprite;

	animWalkLeft.Set(15, 17, 1.f, true, 1, true);
	animWalkRight.Set(27, 29, 1.f, true, 1, true);

	AlertRange = 50.f;
	PatrolRange = 200.f;
	EnemySpeed = 100.f;

	AttackDamage = 10.f;
	TimeBetweenAttack = 1.f;
	AttackCooldown = 0.f;

	collidedWall = false;
}

MeleeEnemy::~MeleeEnemy()
{
	if (state)
		delete state;
}

void MeleeEnemy::Init(TileMap* map)
{
	this->map = map;
}

void MeleeEnemy::Update(double dt)
{
	AttackCooldown -= dt;

	if (state)
		state->Update(dt);
	collidedWall = false;

	if (sprite)
		sprite->Update(dt);
	if (!isGrounded)
		vel.y -= 9.8;

	MapCollision(dt);
}

void MeleeEnemy::Attack(Player* player)
{
	int tmp = player->GetPlayerHealth();

	if (AttackCooldown < 0)
	{
		AttackCooldown = TimeBetweenAttack;
		tmp -= 20;
		player->SetPlayerHealth(tmp);
	}

}

void MeleeEnemy::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (state)
	{
		EnemyStates* tempState = state->CheckState();
		if (state != tempState)
		{
			delete state;
			state = tempState;
 			state->Enter(this, player);
		}
	}
	else
	{
		state = new EnemyIdle();
		state->Enter(this, player);
		AttackRange = scale.x;
	}
}