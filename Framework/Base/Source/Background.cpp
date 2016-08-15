#include "GL\glew.h"

#include "Background.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

Background::Background() :
mesh(nullptr)
{
	pos.SetZero();
	scale.Set(1.f, 1.f, 1.f);
}

Background::~Background()
{
	if (mesh)
		delete mesh;
	mesh = NULL;
}

void Background::LoadBackground(string fileLoc, string name)
{
	mesh = MeshBuilder::GenerateBackground(name, Color(0.f, 0.f, 0.f), 1.f);
	mesh->textureArray[0] = LoadTGA(fileLoc.c_str());
}

void Background::SetScale(Vector3 scale)
{
	this->scale = scale;
}

void Background::SetPosition(Vector3 pos)
{
	this->pos = pos;
}

Mesh* Background::GetMesh()
{
	return this->mesh;
}

Vector3 Background::GetScale()
{
	return this->scale;
}

Vector3 Background::GetPosition()
{
	return this->pos;
}