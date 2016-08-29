#include "EnemySkill.h"
#include "MeshGenerator.h"
#include "Player.h"

EnemySkill::EnemySkill()
{

}

EnemySkill::~EnemySkill()
{

}

void EnemySkill::Init(Vector3 pos, Vector3 scale, int damage)
{
	this->pos = pos;
	this->scale = scale;
	this->damage = damage;
	collider.Init(&this->pos, scale);
}

void EnemySkill::Update(double dt)
{
	sprite->Update(dt);
}

void EnemySkill::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (player)
		if (sprite->m_currentFrame == attackOnFrame)
			if (collider.CheckCollision(player->collider))
				player->TakeDamage(damage);
}

void EnemySkill::SetSprite(string fileLoc, int row, int col, Animation anim)
{
	sprite = MeshGenerator::GetInstance().GenerateSprite("Skill", fileLoc, row, col);
	sprite->SetAnimation(anim);
	mesh = sprite;
}