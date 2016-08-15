#include "MapEditor.h"
#include "Application.h"
#include "MeshGenerator.h"

#include <iostream>
#include <sstream>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;
using std::cin;

MapEditor::MapEditor():
active(false),
showTiles(false),
selectedTile(0),
map(NULL),
rearMap(NULL),
tileSheet(NULL),
collisionbox(NULL),
state(FRONT_MAP)
{
	tilesID.clear();
	collisionbox = MeshGenerator::GenerateTileSheet("Collision Box", "Image//collisionbox.tga", 1, 3);
}

MapEditor::~MapEditor()
{

}

void MapEditor::Init(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void MapEditor::Update(double dt)
{
	if (!map)
	{
		string name;
		cout << "Input map name." << endl;
		cin >> name;
	}
	if (Application::GetInstance().controller->IsKeyPressed(TAB))
		showTiles = true;

	if (Application::GetInstance().controller->IsKeyReleased(TAB))
		showTiles = false;

	if (showTiles)
	{
		if (Application::scrollY > 0)
			offset.y -= 1;
		if (Application::scrollY < 0)
			offset.y += 1;

		if (offset.y < 0)
			offset.y = 0.f;
		if (offset.y > row)
			offset.y = row;
		
		Application::scrollY = 0;

		if (Application::GetInstance().IsMousePressed(0))
		{
			double mouseX, mouseY;
			Application::GetMousePos(mouseX, mouseY);
			int tileX, tileY;
			tileX = mouseX / map->GetTileSize();
			tileY = mouseY / map->GetTileSize();
			tileX += offset.x;
			tileY += offset.y;
			if (tileX < column && tileX >= 0 && tileY >= 0 && tileY < row)
				selectedTile = tilesID[tileY][tileX];
			else
				selectedTile = 0;
		}
	}

	if (Application::GetInstance().controller->IsKeyPressed(ONE))
		state = FRONT_MAP;
	if (Application::GetInstance().controller->IsKeyPressed(TWO))
		state = REAR_MAP;
	if (Application::GetInstance().controller->IsKeyPressed(THREE))
		state = COLLISION_MAP;

	if (Application::GetInstance().IsMousePressed(0))
	{
		double mouseX, mouseY;
		Application::GetMousePos(mouseX, mouseY);
		int tileX, tileY;
		tileX = (mouseX + camera->GetFineOffset()->x) / map->GetTileSize() + camera->GetTileOffset()->x;
		tileY = (mouseY - camera->GetFineOffset()->y) / map->GetTileSize() - camera->GetTileOffset()->y;
		tileY = (map->GetScreenHeight() / map->GetTileSize()) - tileY;
		if (tileX >= 0 && tileX < map->GetNumOfTiles_MapWidth() && tileY >= 0 && tileY < map->GetNumOfTiles_MapWidth())
		{
			switch (state)
			{
			case FRONT_MAP:
				map->theScreenMap[tileY][tileX] = selectedTile;
				break;
			case REAR_MAP:
				rearMap->theScreenMap[tileY][tileX] = selectedTile;
				break;
			case COLLISION_MAP:
				map->theCollisionMap[tileY][tileX] = selectedTile;
				break;
			}

		}
	}

	if (Application::GetInstance().IsMousePressed(1))
	{
		double mouseX, mouseY;
		Application::GetMousePos(mouseX, mouseY);
		int tileX, tileY;
		tileX = (mouseX + camera->GetFineOffset()->x) / map->GetTileSize() + camera->GetTileOffset()->x;
		tileY = (mouseY - camera->GetFineOffset()->y) / map->GetTileSize() - camera->GetTileOffset()->y;
		tileY = (map->GetScreenHeight() / map->GetTileSize()) - tileY;
		if (tileX >= 0 && tileX < map->GetNumOfTiles_MapWidth() && tileY >= 0 && tileY < map->GetNumOfTiles_MapWidth())
			map->theScreenMap[tileY][tileX] = 0;
	}

	if (Application::GetInstance().controller->OnHold(CTRL) && Application::GetInstance().controller->IsKeyPressed(MOVE_DOWN))
	{
		cout << "Please enter file name" << endl;
		string name;
		cin >> name;
		SaveMap(name);
	}
}

void MapEditor::CreateNewMap(int mapWidth, int mapHeight, int tileSize, bool front)
{
	
}

void MapEditor::LoadMap(TileMap* map)
{
	this->map = map;
}

bool MapEditor::LoadMap(string name)
{
	ifstream file;
	string graphicFileLoc = "Image//";
	graphicFileLoc.append(name).append("_Graphic.csv");
	file.open(graphicFileLoc);
	
	if (file.is_open())
	{
		string collisionFileLoc = "Image//";
		collisionFileLoc.append(name).append("_Collision.csv");

		map = new TileMap;
		map->Init(screenHeight, screenWidth, 32);
		map->LoadMap(graphicFileLoc, collisionFileLoc);

		cout << "Input tileSheet name." << endl;
		string tileSheetName;
		cin >> tileSheetName;
		string tileSheetFileLoc = "Image//";
		tileSheetFileLoc.append(tileSheetName).append("tga");
		map->LoadTileSheet(tileSheetFileLoc);
		this->tileSheet = map->GetTileSheet();
		return true;
	}
}

void MapEditor::LoadTileSheet(Mesh* tileSheet, int row, int column)
{
	this->tileSheet = tileSheet;
	this->row = row;
	this->column = column;
	for (int i = 0; i < row; ++i)
	{
		vector<int> columns;
		columns.clear();

		for (int j = 0; j < column; ++j)
		{
			columns.push_back(i * column + j);
		}

		tilesID.push_back(columns);
	}
}

void MapEditor::SaveMap(string name)
{
	ofstream file;
	string fileLoc = "Image//";
	fileLoc.append(name).append("_Graphic.csv");
	file.open(fileLoc, std::ofstream::out);

	for (vector<vector<int> >::reverse_iterator it = map->theScreenMap.rbegin(); it != map->theScreenMap.rend(); ++it)
	{
		vector<int> token = *it;
		std::stringstream iss;
		for (vector<int>::iterator lineIt = token.begin(); lineIt != token.end(); lineIt++)
		{
			int value = *lineIt;
			iss << value << ",";
		}
		iss << '\n';
		file << iss.str();
	}
	file.close();
	cout << "Saved " << fileLoc << " file." << endl;

	if (!map->theCollisionMap.empty())
	{
		fileLoc = "Image//";
		fileLoc.append(name).append("_Collision.csv");
		file.open(fileLoc, std::ofstream::out);

		for (vector<vector<int> >::reverse_iterator it = map->theCollisionMap.rbegin(); it != map->theCollisionMap.rend(); ++it)
		{
			vector<int> token = *it;
			std::stringstream iss;
			for (vector<int>::iterator lineIt = token.begin(); lineIt != token.end(); lineIt++)
			{
				int value = *lineIt;
				iss << value << ",";
			}
			iss << '\n';
			file << iss.str();
		}
		file.close();
	}

	cout << "Saved " << fileLoc << " file." << endl;
}

void MapEditor::SetCamera(CameraFollow* camera)
{
	this->camera = camera;
}

Mesh* MapEditor::GetTileSheet()
{
	return tileSheet;
}

Mesh* MapEditor::GetCollisionBox()
{
	return collisionbox;
}

TileMap* MapEditor::GetMap()
{
	return map;
}

TileMap* MapEditor::GetRearMap()
{
	return rearMap;
}