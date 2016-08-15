#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Key.h"
#include <Windows.h>

enum Controls
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_UP,
	MOVE_DOWN,
	LEFT_CLICK,
	RIGHT_CLICK,
	TAB,
	JUMP,
	ONE,
	TWO,
	THREE,
	EXIT,
	CTRL,
	KEYS_SIZE,
};

class Controller
{
public:
	Controller(){};
	virtual ~Controller(){};
	virtual void create() = 0;
	virtual void read() = 0;
	virtual bool IsKeyPressed(Controls input) const = 0;
	virtual bool OnHold(Controls input) const = 0;
	virtual bool IsKeyReleased(Controls input) const = 0;

	Key keys[KEYS_SIZE];
};

#endif // !CONTROLLER_H
