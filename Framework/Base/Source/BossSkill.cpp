#include "BossSkill.h"
#include "MeshGenerator.h"
#include "Player.h"

BossSkill::BossSkill()
{
	hit = false;
}

BossSkill::~BossSkill()
{

}

void BossSkill::Init(Vector3 pos, Vector3 scale, int damage)
{
	this->pos = pos;
	this->scale = scale;
	this->damage = damage;
	collider.Init(&this->pos, scale);
}

void BossSkill::Update(double dt)
{
	sprite->Update(dt);
	if (sprite->m_anim->ended)
		active = false;
}

void BossSkill::HandleInteraction(GameObject* go, double dt)
{
	Player* player = dynamic_cast<Player*>(go);
	if (player)
		if (sprite->m_currentFrame == attackOnFrame)
			if (collider.CheckCollision(player->collider) && !hit)
			{
				player->TakeDamage(damage);
				hit = true;
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
			}
}

void BossSkill::SetSprite(string fileLoc, int row, int col, Animation anim)
{
	sprite = MeshGenerator::GetInstance().GenerateSprite("Skill", fileLoc, row, col);
	sprite->SetAnimation(anim);
	mesh = sprite;
}