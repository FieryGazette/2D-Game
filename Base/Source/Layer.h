#ifndef LAYER_H
#define LAYER_H
#include "Tile.h"

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
	Layer(const char* filepath);
	~Layer();

	/* Core */
	void addTile(int& x, int& y);

	/* Utilities */
	bool LoadTileLayer();
	void GetTilePos(int tileIndex, Vector3& pos);
	float getTileSize();
	int getTotalTiles();
	void Clear();	//free memory

private:
	/* Info for map */
	int layer;	//what layer is it
	int tileSize;	//tile size for this layer
	bool collidable;	//can collide or not

	/* Tile stuff */
	vector<Tile*> TileMap;

	/* tileMap */
	const char* filepath;	//file path to the txt
};

#endif