#include "MapEditor.h"
#include "Application.h"
#include "MeshGenerator.h"
#include "AABB_2D.h"

#include <iostream>
#include <sstream>
#include <fstream>

using std::stoi;
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
editorState(SETUP),
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
	this->tileSize = tileSize;
}

bool MapEditor::TextInput(string& text)
{
	char c = (char)Application::GetInstance().key;
	if (c != 0)
	{
		Application::GetInstance().key = 0;
		text += c;
	}

	if (Application::GetInstance().controller->IsKeyPressed(BACKSPACE))
	{
		if (!text.empty())
			text.pop_back();
	}

	if (Application::GetInstance().controller->IsKeyPressed(ENTER))
	{
		return true;
	}
	
	return false;
}

void MapEditor::Update(double dt)
{
	switch (editorState)
	{
	case SETUP:
		Setup();
		break;
	case CREATE:
		Create();
		break;
	case LOAD:
		Load();
		break;
	case EDIT:
		Edit();
		break;
	}
}

void MapEditor::Setup()
{
	text = "Do you want to create a new level?";
	if (Application::GetInstance().IsMousePressed(0))
	{
		double mouseX, mouseY;
		Application::GetInstance().GetMousePos(mouseX, mouseY);
		mouseY = Application::GetInstance().m_window_height - mouseY;
		mouseY = (mouseY / Application::GetInstance().m_window_height) * 600;
		mouseX = (mouseX / Application::GetInstance().m_window_width) * 800;
		Vector3 mousePos(mouseX, mouseY, 1.f);
		AABB_2D yesBox;
		yesBox.Init(Vector3(250.f, 150.f, 1.f), Vector3(200.f, 100.f, 1.f));
		AABB_2D noBox;
		noBox.Init(Vector3(550.f, 150.f, 1.f), Vector3(200.f, 100.f, 1.f));
		if (yesBox.CheckCollision(mousePos))
			editorState = CREATE;
		else if (noBox.CheckCollision(mousePos))
			editorState = LOAD;
	}
}

void MapEditor::Create()
{
	static bool column = false;
	static bool row = false;
	static bool named = false;
	static int columnCount = 0;
	static int rowCount = 0;
	if (!column)
	{
		text = "Please input amount of columns";
		if (TextInput(answer))
		{
			column = true;
			columnCount = stoi(answer);
			answer.clear();
		}
	}
	else if (!row && column)
	{
		text = "Please input amount of rows";
		if (TextInput(answer))
		{
			row = true;
			rowCount = stoi(answer);
			answer.clear();
		}
	}
	else if (!named)
	{
		text = "Please name the level.";
		if (TextInput(answer))
		{
			name = answer;
			CreateNewMap(columnCount, rowCount);
			editorState = EDIT;
		}
	}
}

void MapEditor::Load()
{
	text = "Please enter the name of the level.";
	if (TextInput(name))
	{
		if (LoadMap(name, tileSize))
		{
			editorState = EDIT;
			camera->SetMap(map);
		}
		else
			name.clear();
	}
}

void MapEditor::Edit()
{
	map->Init(screenHeight, screenWidth, 32);

	if (Application::GetInstance().controller->IsKeyPressed(TAB))
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
			mouseY = (mouseY / Application::GetInstance().m_window_height) * 600;
			mouseX = (mouseX / Application::GetInstance().m_window_width) * 800;

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
			mouseY = Application::GetInstance().m_window_height - mouseY;
			mouseY = (mouseY / Application::GetInstance().m_window_height) * 600;
			mouseX = (mouseX / Application::GetInstance().m_window_width) * 800;
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
			mouseY = Application::GetInstance().m_window_height - mouseY;
			mouseY = (mouseY / Application::GetInstance().m_window_height) * 600;
			mouseX = (mouseX / Application::GetInstance().m_window_width) * 800;
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
			mouseY = Application::GetInstance().m_window_height - mouseY;
			mouseY = (mouseY / Application::GetInstance().m_window_height) * 600;
			mouseX = (mouseX / Application::GetInstance().m_window_width) * 800;
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
	}
}

void MapEditor::CreateNewMap(int numOfTilesWidth, int numOfTilesHeight)
{
	map = new TileMap();
	map->Create(screenWidth, screenHeight, numOfTilesWidth, numOfTilesHeight, this->tileSize);
	camera->SetMap(map);
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