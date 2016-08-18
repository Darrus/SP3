#include "MeleeEnemy.h"
#include "EnemyIdle.h"
#include "MeshGenerator.h"

MeleeEnemy::MeleeEnemy() :
AlertRange(50),
EnemySpeed(50)
{
	sprite = MeshGenerator::GetInstance().GenerateSprite("Goblin", "Image//enemysprite.tga", 8, 12);
	mesh = sprite;

	animWalkLeft.Set(15, 17, 1.f, true, 1, true);
	animWalkRight.Set(27, 29, 1.f, true, 1, true);
}

MeleeEnemy::~MeleeEnemy()
{

}

void MeleeEnemy::Init(TileMap* map)
{
	this->map = map;
	state = new EnemyIdle();
	state->Enter(*this, *player);
}

void MeleeEnemy::Update(double dt)
{
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