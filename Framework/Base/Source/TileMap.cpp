#include "GL\glew.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include "TileMap.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

using std::istringstream;
using std::ifstream;
using std::cout;
using std::endl;

TileMap::TileMap() :
screenHeight(0),
screenWidth(0),
mapHeight(0),
mapWidth(0),
tileSize(0),
numOfTiles_ScreenHeight(0),
numOfTiles_ScreenWidth(0),
numOfTiles_MapHeight(0),
numOfTiles_MapWidth(0),
tileOffsetX(0),
tileOffsetY(0),
fineOffsetX(0),
fineOffsetY(0),
tileSheet(NULL)
{
	frontMap.clear();
	rearMap.clear();
	collisionMap.clear();
}

TileMap::~TileMap()
{
	if (!frontMap.empty())
		frontMap.clear();

	if (!rearMap.empty())
		rearMap.clear();

	if (!collisionMap.empty())
		collisionMap.clear();

	if (tileSheet)
		delete tileSheet;
	tileSheet = NULL;
}

void TileMap::Init(int screenHeight, int screenWidth, const int tileSize)
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->tileSize = tileSize;
	this->numOfTiles_ScreenHeight = ceil((float)screenHeight / (float)tileSize);
	this->numOfTiles_ScreenWidth = ceil((float)screenWidth / (float)tileSize);
}

void TileMap::Create(int screenWidth, int screenHeight, const int numOfTiles_MapWidth, const int numOfTiles_MapHeight, const int tileSize)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->tileSize = tileSize;
	this->numOfTiles_MapWidth = numOfTiles_MapWidth;
	this->numOfTiles_MapHeight = numOfTiles_MapHeight;
	this->mapWidth = numOfTiles_MapWidth * tileSize;
	this->mapHeight = numOfTiles_MapHeight * tileSize;
	this->numOfTiles_ScreenWidth = ceil((float)screenWidth / tileSize);
	this->numOfTiles_ScreenHeight = ceil((float)screenHeight / tileSize);

	for (int i = 0; i < numOfTiles_MapHeight; ++i)
	{
		vector<int > row;
		row.clear();
		for (int k = 0; k < numOfTiles_MapWidth; ++k)
		{
			row.push_back(0);
		}

		frontMap.push_back(row);
		rearMap.push_back(row);
		collisionMap.push_back(row);
	}
}

bool TileMap::LoadMap(const string name)
{
	string fileLoc = "Maps\\";
	fileLoc.append(name);
	if (!LoadFile(fileLoc + "_front.csv", frontMap))
	{
		cout << "Failed loading front map." << endl;
		frontMap.clear();
		return false;
	}
	if (!LoadFile(fileLoc + "_rear.csv", rearMap))
	{
		cout << "Failed loading rear map." << endl;
		frontMap.clear();
		return false;
	}
	if (!LoadFile(fileLoc + "_collision.csv", collisionMap))
	{
		cout << "Failed loading collision map." << endl;
		frontMap.clear();
		return false;
	}
	return true;
}

bool TileMap::LoadTileSheet(const string fileLoc)
{
	if (!tileSheet)
	{
		tileSheet = MeshBuilder::GenerateTileSheet("Tile Sheet", 16, 16);
		tileSheet->textureArray[0] = LoadTGA(fileLoc.c_str());
		return true;
	}
	else
		return false;
}

bool TileMap::LoadFile(const string mapName, vector<vector<int> >& map)
{
	int rows = 0;
	bool first = true;
	int columnCheck = 0;
	ifstream file(mapName.c_str());
	vector<string> lineOfTexts;

	if (file.is_open())
	{
		while (file.good())
		{
			string aLineOfText = "";
			getline(file, aLineOfText);
			if (aLineOfText != "")
				lineOfTexts.push_back(aLineOfText);
		}
	}
	else
	{
		cout << "Error opening file" << mapName << '.' << endl;
		return false;
	}

	file.close();

	while (!lineOfTexts.empty())
	{
		string aLineOfText = lineOfTexts.back();
		string token = "";
		istringstream iss(aLineOfText);
		vector<int> store;

		while (getline(iss, token, ','))
		{
			store.push_back(stoi(token));
			if (first)
				columnCheck++;
		}

		if (store.size() != columnCheck)
		{
			cout << "Error loading map at Row " << rows << ". Does not match amount of columns as first row." << endl;
			return false;
		}

		first = false;
		map.push_back(store);
		rows++;
		lineOfTexts.pop_back();
	}

	mapWidth = columnCheck * tileSize;
	mapHeight = rows * tileSize;
	numOfTiles_MapWidth = columnCheck;
	numOfTiles_MapHeight = rows;
	cout << "Succesfully Loaded " << mapName << '.' << endl;
	return true;
}

Mesh* TileMap::GetTileSheet()
{
	return tileSheet;
}

int TileMap::GetNumOfTiles_ScreenHeight()
{
	return numOfTiles_ScreenHeight;
}

int TileMap::GetNumOfTiles_ScreenWidth()
{
	return numOfTiles_ScreenWidth;
}

int TileMap::GetNumOfTiles_MapHeight()
{
	return numOfTiles_MapHeight;
}

int TileMap::GetNumOfTiles_MapWidth()
{
	return numOfTiles_MapWidth;
}

int TileMap::GetScreenHeight()
{
	return screenHeight;
}

int TileMap::GetScreenWidth()
{
	return screenWidth;
}

int TileMap::GetTileSize()
{
	return tileSize;
}

int TileMap::GetMapWidth()
{
	return mapWidth;
}

int TileMap::GetMapHeight()
{
	return mapHeight;
}
