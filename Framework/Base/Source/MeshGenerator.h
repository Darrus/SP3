#ifndef MESH_GENERATOR_H
#define MESH_GENERATOR_H

#include <string>
#include <vector>
#include "SpriteAnimation.h"
#include "Vertex.h"

using std::string;
using std::vector;

class MeshGenerator
{
private:
	vector<Mesh*> store;

public:
	MeshGenerator();
	~MeshGenerator();

	static MeshGenerator& GetInstance();

	SpriteAnimation* GenerateSprite(string name, string textureLoc, int row, int column);
	Mesh* GenerateQuad(string name, Color color, string textureLoc, float size = 1.f);
	Mesh* Generate2D(string name, Color color, string textureLoc, float size = 1.f);
	Mesh* GenerateTileSheet(string name, string textureLoc, int row, int column);
};

#endif