#ifndef ENEMY_STUN_H
#define ENEMY_STUN_H

#include "EnemyStates.h"

class EnemyStun : public EnemyStates
{
public:
	EnemyStun();
	virtual ~EnemyStun();

	virtual void Enter(Enemy* enemy, Player* player);
	virtual EnemyStates* CheckState();

	bool end;
};


#endif