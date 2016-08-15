#include "GL\glew.h"

#include "MeshGenerator.h"
#include "LoadTGA.h"
#include "MeshBuilder.h"
#include <iostream>

using std::cout;
using std::endl;

MeshGenerator::MeshGenerator()
{

}

MeshGenerator::~MeshGenerator()
{
}

SpriteAnimation* MeshGenerator::GenerateSprite(string name, string textureLoc, int row, int column)
{
	SpriteAnimation* mesh;
	mesh = MeshBuilder::GenerateSpriteAnimation(name, row, column);
	mesh->textureArray[0] = LoadTGA(textureLoc.c_str());
	return mesh;
}

Mesh* MeshGenerator::GenerateQuad(string name, Color color, string textureLoc, float size)
{
	Mesh* mesh;
	mesh = MeshBuilder::GenerateQuad(name, color, size);
	mesh->textureArray[0] = LoadTGA(textureLoc.c_str());
	return mesh;
}

Mesh* MeshGenerator::Generate2D(string name, Color color, string textureLoc, float size)
{
	Mesh* mesh;
	mesh = MeshBuilder::Generate2DMesh(name, color, 0, 0, 1, 1);
	mesh->textureArray[0] = LoadTGA(textureLoc.c_str());
	return mesh;
}

Mesh* MeshGenerator::GenerateTileSheet(string name, string textureLoc, int row, int column)
{
	Mesh* mesh;
	mesh = MeshBuilder::GenerateTileSheet(name, row, column);
	mesh->textureArray[0] = LoadTGA(textureLoc.c_str());
	return mesh;
}