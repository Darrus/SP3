#include "GL\glew.h"

#include "ParallaxBackground.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include <sstream>
#include <iostream>

using std::stringstream;
using std::cout;
using std::endl;

ParallaxBackground::ParallaxBackground() :
bgCount(0),
MAX_BACKGROUNDS(4),
smoothing(1.f)
{
	backgrounds = new Background*[MAX_BACKGROUNDS];
	for (int i = 0; i < MAX_BACKGROUNDS; ++i)
	{
		backgrounds[i] = nullptr;
	}
}

ParallaxBackground::~ParallaxBackground()
{
	while (bgCount >= 0)
	{
		delete backgrounds[bgCount];
		backgrounds[bgCount] = NULL;
		bgCount--;
	}

	delete[] backgrounds;
}

void ParallaxBackground::Init(Vector3* cameraPos, int screenWidth, int screenHeight)
{
	this->cameraPos = cameraPos;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void ParallaxBackground::Update()
{
	for (int i = 0; i < bgCount; ++i)
	{
		float parallaxX = cameraPos->x * 0.2f * (i + smoothing);
		float parralaxY = cameraPos->y * 0.2f * (i + smoothing);

		backgrounds[i]->SetPosition(Vector3((cameraPos->x + backgrounds[i]->GetScale().x * 0.5f) - parallaxX, (cameraPos->y + backgrounds[i]->GetScale().y * 0.5f) - parralaxY, 0.f));
	}
}

void ParallaxBackground::LoadBackground(string fileLoc, Vector3 scale)
{
	if (bgCount < MAX_BACKGROUNDS)
	{
		backgrounds[bgCount] = new Background();
		backgrounds[bgCount]->SetScale(scale);
		stringstream name;
		name << "Background " << bgCount;
		backgrounds[bgCount]->LoadBackground(fileLoc, name.str());
		bgCount++;
	}
	else
		cout << "Reached maximum allowed backgrounds." << endl;
}

void ParallaxBackground::ClearBackgrounds()
{
	delete[] backgrounds;
	bgCount = 0;
}

void ParallaxBackground::SetCameraPos(Vector3* pos)
{
	this->cameraPos = cameraPos;
}

int ParallaxBackground::GetBackgroundCount()
{
	return bgCount;
}

Background* ParallaxBackground::GetBackground(int count)
{
	return backgrounds[count];
}