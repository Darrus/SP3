#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <string>

#include "TileMap.h"
#include "Vector2.h"
#include "CameraFollow.h"

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

	void Init(int screenWidth, int screenHeight);
	void Update(double dt);
	
	void CreateNewMap(int mapWidth, int mapHeight, int tileSize);
	void LoadMap(TileMap* map);
	bool LoadMap(string name, int tileSize);
	void LoadRearMap(TileMap* map);
	void LoadTileSheet(string name, int row, int column);
	void SetCamera(CameraFollow* camera);

	void SaveMap(string name);

	Mesh* GetTileSheet();
	Mesh* GetCollisionBox();
	TileMap* GetMap();
	EDIT_STATE GetState();

	bool active;
	bool showMap[STATE_SIZE];
	bool showTiles;
	int row, column;
	vector<vector<int> > tilesID;
	Vector2 offset;

private:

	string name;

	TileMap* map;

	Mesh* tileSheet;
	Mesh* collisionbox;

	int selectedTile;
	int screenWidth, screenHeight;

	CameraFollow* camera;
	EDIT_STATE state;
	
};

#endif