#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Controller.h"

class Keyboard : public Controller
{
public:
	Keyboard();
	virtual ~Keyboard();

	virtual void create();
	virtual void read();

	virtual bool IsKeyPressed(Controls input) const;
	virtual bool OnHold(Controls input) const;
	virtual bool IsKeyReleased(Controls input) const;
};

#endif // !KEYBOARD_H
