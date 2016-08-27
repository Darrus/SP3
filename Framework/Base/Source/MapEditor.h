#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <string>

#include "TileMap.h"
#include "Vector2.h"
#include "CameraFree.h"

using std::string;

class MapEditor
{
public:
	enum EDITOR_STATE
	{
		SETUP,
		CREATE,
		LOAD,
		EDIT
	};

	enum EDIT_STATE
	{
		REAR_MAP,
		FRONT_MAP,
		COLLISION_MAP,
		STATE_SIZE,
	};

	MapEditor();
	~MapEditor();

	void Init(int *screenWidth, int *screenHeight, int tileSize);
	void Update(double dt);
	
	
	void CreateNewMap(int numOfTilesWidth, int numOfTilesHeight);
	void LoadMap(TileMap* map);
	bool LoadMap(string name, int tileSize);
	void LoadRearMap(TileMap* map);
	void LoadTileSheet(string name, int row, int column);
	void SetCamera(CameraFree* camera);
	bool TextInput(string& text);
	void SaveMap(string name);

	TileMap* GetMap();
	EDIT_STATE GetState();

	bool active;
	bool showMap[STATE_SIZE];
	bool showTiles;
	int row, column;
	vector<vector<int> > tilesID;
	Vector2 offset;

	Mesh* tileSheet;
	Mesh* collisionbox;
	Mesh* mapbackground;

	string name;
	string text;
	string answer;
	EDITOR_STATE editorState;
	int selectedTile;

private:
	void Setup();
	void Create();
	void Load();
	void Edit();

	TileMap* map;
	int *screenWidth, *screenHeight;
	int tileSize;
	CameraFree* camera;
	EDIT_STATE state;
};

#endif