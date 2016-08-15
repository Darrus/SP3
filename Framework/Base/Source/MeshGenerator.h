#ifndef MESH_GENERATOR_H
#define MESH_GENERATOR_H

#include <string>
#include "SpriteAnimation.h"
#include "Vertex.h"

using std::string;

class MeshGenerator
{
public:
	MeshGenerator();
	~MeshGenerator();

	static SpriteAnimation* GenerateSprite(string name, string textureLoc, int row, int column);
	static Mesh* GenerateQuad(string name, Color color, string textureLoc, float size = 1.f);
	static Mesh* Generate2D(string name, Color color, string textureLoc, float size = 1.f);
	static Mesh* GenerateTileSheet(string name, string textureLoc, int row, int column);
};

#endif