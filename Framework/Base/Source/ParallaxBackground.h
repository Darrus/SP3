#ifndef PARALLAX_BACKGROUND_H
#define PARALLAX_BACKGROUND_H

#include <string>
#include "Vector3.h"
#include "Background.h"

using std::string;

class ParallaxBackground
{
public:
	ParallaxBackground();
	~ParallaxBackground();

	void Init(Vector3* cameraPos, int screenWidth, int screenHeight);
	void Update();
	void LoadBackground(string fileLoc, Vector3 scale);
	void ClearBackgrounds();

	void SetCameraPos(Vector3* pos);

	int GetBackgroundCount();
	Background* GetBackground(int count);
private:
	const int MAX_BACKGROUNDS;
	Background** backgrounds;
	int bgCount;
	Vector3* cameraPos;
	int screenWidth, screenHeight;
	float smoothing;
};

#endif