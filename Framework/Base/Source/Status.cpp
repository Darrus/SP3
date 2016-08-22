#include "Status.h"

Status::Status() :
end(false),
duration(0.f),
name("")
{

}

Status::~Status()
{

}

void Status::Update(double dt)
{
	duration -= dt;
	if (duration < 0)
		end = true;
}

void Status::ApplyStatus(GameObject* go)
{

}

void Status::RevertStatus()
{

}

void Status::SetDuration(float duration)
{
	this->duration = duration;
}

string Status::GetName()
{
	return name;
}

float Status::GetDuration()
{
	return duration;
}