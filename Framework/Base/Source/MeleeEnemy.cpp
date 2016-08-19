#include "MeleeEnemy.h"
#include "EnemyIdle.h"
#include "MeshGenerator.h"

MeleeEnemy::MeleeEnemy()
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
	state = new EnemyIdle();
	state->Enter(this, player);
	AttackRange = scale.x + player->scale.x;
}

void MeleeEnemy::Update(double dt)
{
	EnemyStates* tempState = state->CheckState();
	AttackCooldown -= dt;
	if (state != tempState)
	{
		delete state;
		state = tempState;
		state->Enter(this, player);
	}

	if (state)
		state->Update(dt);

	collidedWall = false;

	if (sprite)
		sprite->Update(dt);
	if (!isGrounded)
		vel.y -= 9.8;

	MapCollision(dt);
}

void MeleeEnemy::HandleInteraction(GameObject* go, double dt)
{

}