#ifndef LAYER_H
#define LAYER_H
#include "Tile.h"
#include "MeshList.h"

/*****************************************************************/
/*
	Layer class. Contains map of tiles. Each tile contains just X and Y pos in map.
	To be translated into actual pos in render. X * tileSize and Y * tilesize.
	Position NOT determined by index in vector.
*/
/*****************************************************************/
class Layer
{
public:
	/* Constructor/destructor */
	Layer();
	Layer(Geometry::TILE_MAP tileMap);
	~Layer();

	/* Core */
	//if is existing tile, will edit that existing tile instead
	void addTile(int& x, int& y);
	void editTile(int type);	//pass in tile type

	/* Utilities */
	bool LoadTileLayer();
	void GetTilePos(int tileIndex, Vector3& pos);	//for looping use
	float getTileSize();
	int getTotalTiles();
	void Clear();	//free memory

private:
	/* Info for map */
	int layer;	//what layer is it
	int tileSize;	//tile size for this layer
	bool collidable;	//this layer can collide or not
	bool edited;	//is it edited?

	/* Tile stuff */
	vector<Tile*> TileMap;

	/* tileMap */
	Geometry::TILE_MAP tileMap;	//what tilemap
};

#endif