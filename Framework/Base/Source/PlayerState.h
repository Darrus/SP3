#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "Player.h"

class PlayerState
{
public:
	PlayerState();
	~PlayerState();

	virtual void HandleInput()
};

#endif