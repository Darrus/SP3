#include "GameObject.h"

GameObject::GameObject() :
mesh(NULL),
active(false)
{
	pos.SetZero();
	scale.Set(1.f, 1.f, 1.f);
	view.SetZero();
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::Update(double dt)
{
}

void GameObject::HandleInteraction(GameObject* go, double dt)
{

}