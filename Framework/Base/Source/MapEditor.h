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
	enum EDIT_STATE
	{
		REAR_MAP,
		FRONT_MAP,
		COLLISION_MAP,
		STATE_SIZE,
	};

	MapEditor();
	~MapEditor();

	void Init(int screenWidth, int screenHeight, int tileSize);
	void Update(double dt);
	
	void CreateNewMap(int mapWidth, int mapHeight, int tileSize);
	void LoadMap(TileMap* map);
	bool LoadMap(string name, int tileSize);
	void LoadRearMap(TileMap* map);
	void LoadTileSheet(string name, int row, int column);
	void SetCamera(CameraFree* camera);

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

private:

	string name;

	TileMap* map;

	int selectedTile;
	int screenWidth, screenHeight;

	CameraFree* camera;
	EDIT_STATE state;
	
};

#endif