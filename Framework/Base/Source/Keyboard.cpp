#include "Keyboard.h"
#include "Application.h"
Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{

}

void Keyboard::create()
{
	keys[MOVE_UP].Assign('W');
	keys[MOVE_DOWN].Assign('S');
	keys[MOVE_FORWARD].Assign('W');
	keys[MOVE_BACKWARD].Assign('S');
	keys[MOVE_LEFT].Assign('A');
	keys[MOVE_RIGHT].Assign('D');
	keys[ONE].Assign('1');
	keys[TWO].Assign('2');
	keys[THREE].Assign('3');
	keys[TAB].Assign(VK_TAB);
	keys[JUMP].Assign(VK_SPACE);
	keys[CTRL].Assign(VK_CONTROL);
	keys[EXIT].Assign(VK_ESCAPE);
	keys[CYCLEBULLET].Assign('Q');
	keys[USEITEM].Assign('E');
}

void Keyboard::read()
{
	for (int i = 0; i < KEYS_SIZE; ++i)
	{
		if ((GetAsyncKeyState(keys[i].key) & 0x8001) != 0)
		{
			if (keys[i].isPressed)
				keys[i].onHold = true;
			else
				keys[i].isPressed = true;
		}
		else if (keys[i].isPressed || keys[i].onHold)
		{
			keys[i].onHold = false;
			keys[i].isPressed = false;
			keys[i].isReleased = true;
		}
		else if (keys[i].isReleased)
			keys[i].isReleased = false;

	}
}

bool Keyboard::IsKeyPressed(Controls input) const
{
	return keys[input].isPressed;
}
bool Keyboard::OnHold(Controls input) const
{
	return keys[input].onHold;
}

bool Keyboard::IsKeyReleased(Controls input) const
{
	return keys[input].isReleased;
}