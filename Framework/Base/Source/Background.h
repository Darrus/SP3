#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Vector3.h"
#include "Mesh.h"
#include <string>

using std::string;

class Background
{
public:
	Background();
	~Background();

	void LoadBackground(string fileLoc, string name);
	
	void SetScale(Vector3 scale);
	void SetPosition(Vector3 pos);

	Mesh* GetMesh();
	Vector3 GetScale();
	Vector3 GetPosition();

private:
	Vector3 pos;
	Vector3 scale;

	Mesh* mesh;
};

#endif