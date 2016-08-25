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
tileSheet(NULL),
collisionbox(NULL),
name(""),
state(REAR_MAP),
camera(NULL)
{
	tilesID.clear();
	collisionbox = MeshGenerator::GetInstance().GenerateTileSheet("Collision Box", "Image//collisionbox.tga", 1, 3);
	mapbackground = MeshGenerator::GetInstance().GenerateQuad("Map background", Color(1.f, 1.f, 1.f), "Image//mapbackground.tga");
	for (int i = 0; i < MapEditor::STATE_SIZE; ++i)
	{
		showMap[i] = true;
	}
}

MapEditor::~MapEditor()
{

}

void MapEditor::Init(int screenWidth, int screenHeight, int tileSize)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	/*if (!map)
	{
		bool answer = true;
		cout << "Create new map?" << endl;
		cout << "0) Yes" << endl;
		cout << "1) No" << endl;
		cin >> answer;

		if (answer == false)
		{
			int mapWidth, mapHeight, tileSize;
			cout << "Please type in the Map's width." << endl;
			cin >> mapWidth;
			cout << "Please type in the Map's height." << endl;
			cin >> mapHeight;
			cout << "Please type in the Map's tile size." << endl;
			cin >> tileSize;

			CreateNewMap(mapWidth, mapHeight, tileSize);
		}
		else
		{
			cout << "Input name of map" << endl;
			cin >> name;
			if (!LoadMap(name, tileSize))
				return;
		}
	}

	if (!tileSheet)
	{
		string tilename;
		cout << "Input name of tilesheet" << endl;
		cin >> tilename;
		cout << "Please input tile sheet's rows" << endl;
		cin >> row;
		cout << "Please input tile sheet's cols" << endl;
		cin >> column;
		LoadTileSheet(tilename, row, column);
	}*/
}

void MapEditor::Update(double dt)
{
	
	char c = (char)Application::GetInstance().key;
	if (c != 0)
		name += c;
	
	/*if (Application::GetInstance().controller->IsKeyPressed(TAB))
		showTiles = true;

	if (Application::GetInstance().controller->IsKeyReleased(TAB))
		showTiles = false;

	if (showTiles)
	{
		if (Application::scrollY > 0)
			offset.y -= 1;
		if (Application::scrollY < 0 && offset.y + map->GetNumOfTiles_ScreenHeight() < row)
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
			if (state != COLLISION_MAP)
			{
				tileX += offset.x;
				tileY += offset.y;
				if (tileX < column && tileX >= 0 && tileY >= 0 && tileY < row)
					selectedTile = tilesID[tileY][tileX];
				else
					selectedTile = 0;
			}
			else
			{
				if (tileX < column && tileX >= 0 && tileY >= 0 && tileY < row)
					selectedTile = tilesID[tileY][tileX];
			}
		}
	}

	if (Application::GetInstance().controller->IsKeyPressed(ONE))
		state = REAR_MAP;
	if (Application::GetInstance().controller->IsKeyPressed(TWO))
		state = FRONT_MAP;
	if (Application::GetInstance().controller->IsKeyPressed(THREE))
	{
		state = COLLISION_MAP;
		selectedTile = 0;
	}

	if (Application::GetInstance().controller->IsKeyPressed(SHOW_REAR))
		showMap[0] = !showMap[0];
	if (Application::GetInstance().controller->IsKeyPressed(SHOW_FRONT))
		showMap[1] = !showMap[1];
	if (Application::GetInstance().controller->IsKeyPressed(SHOW_COLLISION))
		showMap[2] = !showMap[2];

	if (!showTiles)
	{
		if (Application::GetInstance().IsMousePressed(0))
		{
			double mouseX, mouseY;
			int tileX, tileY;
			Application::GetMousePos(mouseX, mouseY);
			mouseY = screenHeight - mouseY;
			tileX = (mouseX + camera->GetFineOffset().x) / map->GetTileSize() + camera->GetTileOffset().x;
			tileY = (mouseY + camera->GetFineOffset().y) / map->GetTileSize() + camera->GetTileOffset().y;

			if (tileX >= 0 && tileX < map->GetNumOfTiles_MapWidth() && tileY >= 0 && tileY < map->GetNumOfTiles_MapWidth())
			{
				switch (state)
				{
				case FRONT_MAP:
					map->frontMap[tileY][tileX] = selectedTile;
					break;
				case REAR_MAP:
					map->rearMap[tileY][tileX] = selectedTile;
					break;
				case COLLISION_MAP:
					map->collisionMap[tileY][tileX] = selectedTile;
					break;
				}

			}
		}

		if (Application::GetInstance().IsMousePressed(2))
		{
			double mouseX, mouseY;
			int tileX, tileY;
			Application::GetMousePos(mouseX, mouseY);
			mouseY = screenHeight - mouseY;
			tileX = (mouseX + camera->GetFineOffset().x) / map->GetTileSize() + camera->GetTileOffset().x;
			tileY = (mouseY + camera->GetFineOffset().y) / map->GetTileSize() + camera->GetTileOffset().y;

			switch (state)
			{
			case FRONT_MAP:
				selectedTile = map->frontMap[tileY][tileX];
				break;
			case REAR_MAP:
				selectedTile = map->rearMap[tileY][tileX];
				break;
			case COLLISION_MAP:
				selectedTile = map->collisionMap[tileY][tileX];
				break;
			}
		}

		if (Application::GetInstance().IsMousePressed(1))
		{
			double mouseX, mouseY;
			int tileX, tileY;
			Application::GetMousePos(mouseX, mouseY);
			mouseY = screenHeight - mouseY;
			tileX = (mouseX + camera->GetFineOffset().x) / map->GetTileSize() + camera->GetTileOffset().x;
			tileY = (mouseY + camera->GetFineOffset().y) / map->GetTileSize() + camera->GetTileOffset().y;

			if (tileX >= 0 && tileX < map->GetNumOfTiles_MapWidth() && tileY >= 0 && tileY < map->GetNumOfTiles_MapWidth())
			{
				switch (state)
				{
				case FRONT_MAP:
					map->frontMap[tileY][tileX] = 0;
					break;
				case REAR_MAP:
					map->rearMap[tileY][tileX] = 0;
					break;
				case COLLISION_MAP:
					map->collisionMap[tileY][tileX] = 0;
					break;
				}
			}
		}
	}

	if (Application::GetInstance().controller->OnHold(CTRL) && Application::GetInstance().controller->IsKeyPressed(MOVE_DOWN))
	{
		if (name == "")
		{
			cout << "Please enter file name" << endl;
			cin >> name;
		}
		SaveMap(name);
	}*/
}

void MapEditor::CreateNewMap(int mapWidth, int mapHeight, int tileSize)
{
	map = new TileMap();
	map->Create(screenWidth, screenHeight, mapWidth, mapHeight, tileSize);
}

void MapEditor::LoadMap(TileMap* map)
{
	this->map = map;
}

bool MapEditor::LoadMap(string name, int tileSize)
{
	map = new TileMap();
	map->Init(screenHeight, screenWidth, tileSize);
	return map->LoadMap(name);
}

void MapEditor::LoadTileSheet(string name, int row, int column)
{
	this->tileSheet = MeshGenerator::GetInstance().GenerateTileSheet(name, "Image\\" + name + ".tga", row, column);
	int size = row * column;
	this->column = 3;
	this->row = size / this->column;
	for (int i = 0; i < this->row; ++i)
	{
		vector<int> columns;
		columns.clear();

		for (int j = 0; j < this->column; ++j)
		{
			columns.push_back(i * this->column + j);
		}

		tilesID.push_back(columns);
	}
}

void MapEditor::SaveMap(string name)
{
	ofstream file;
	string fileLoc = "Maps\\";
	fileLoc.append(name);

	// Save Front Map
	file.open(fileLoc + "_front.csv", std::ofstream::out | std::ofstream::trunc);
	if (file.is_open())
	{
		for (vector<vector<int> >::reverse_iterator it = map->frontMap.rbegin(); it != map->frontMap.rend(); ++it)
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
	
	// Save Rear Map
	file.open(fileLoc + "_rear.csv", std::ofstream::out);
	for (vector<vector<int> >::reverse_iterator it = map->rearMap.rbegin(); it != map->rearMap.rend(); ++it)
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

	// Save Collision Map
	file.open(fileLoc + "_collision.csv", std::ofstream::out);
	for (vector<vector<int> >::reverse_iterator it = map->collisionMap.rbegin(); it != map->collisionMap.rend(); ++it)
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
	cout << "Saved " << name << " file." << endl;
}

void MapEditor::SetCamera(CameraFree* camera)
{
	this->camera = camera;
}

TileMap* MapEditor::GetMap()
{
	return map;
}

MapEditor::EDIT_STATE MapEditor::GetState()
{
	return state;
}