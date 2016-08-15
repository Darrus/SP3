#ifndef KEY_H
#define KEY_H

class Key
{
public:
	Key() : isPressed(false), onHold(false), isReleased(false){};
	~Key(){};

	void Assign(unsigned short key)
	{
		this->key = key;
	}

	unsigned short key;
	bool isPressed;
	bool onHold;
	bool isReleased;
};

#endif