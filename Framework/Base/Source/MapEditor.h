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
	MapEditor();
	~MapEditor();

	void Init(int screenWidth, int screenHeight);
	void Update(double dt);
	
	void CreateNewMap(int mapWidth, int mapHeight, int tileSize, bool collision);
	void LoadMap(TileMap* map);
	bool LoadMap(string name);
	void LoadRearMap(TileMap* map);
	void LoadTileSheet(Mesh* tileSheet, int row, int column);
	void SetCamera(CameraFollow* camera);

	void SaveMap(string name);

	Mesh* GetTileSheet();
	Mesh* GetCollisionBox();
	TileMap* GetMap();
	TileMap* GetRearMap();

	bool active;
	bool showTiles;
	int row, column;
	vector<vector<int> > tilesID;
	Vector2 offset;

private:
	enum EDIT_STATE
	{
		FRONT_MAP,
		REAR_MAP,
		COLLISION_MAP,
	};

	TileMap* map;
	TileMap* rearMap;

	Mesh* tileSheet;
	Mesh* collisionbox;

	int selectedTile;
	int screenWidth, screenHeight;

	CameraFollow* camera;
	EDIT_STATE state;
	
};

#endif