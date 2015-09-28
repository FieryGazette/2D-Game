#ifndef MAP_H
#define MAP_H
#include "Layer.h"

/*****************************************************************/
/*
	Manages layers.
*/
/*****************************************************************/
class Map
{
private:
	/* Layers */
	vector<Layer*> layerList;
	int totalLayers;
	string name;

	/* Utilities */
	static float offset;	//offset btw diff layers
	static Layer* layer_ptr;
	static Tile* tile_ptr;
	static Vector3 global_vec;
public:
	/* Constructor/destructor */
	Map(string name);
	~Map();

	/* Core */
	void AddLayer(Geometry::TILE_MAP tileMap);
	//pass in index of layer, x pos and y pos
	void AddTile(int layerIndex, int& x, int& y);
	bool deleteLayer(int layerNum);
	void Clear();

	/* Get data */
	//pass in which layer, tile index and pos variable
	void GetPosOfTile(int layerIndex, int tileIndex, Vector3& pos);	//T: tile exists	F: out of range
	float getTileSize(int layerIndex);
	int getLayerSize(int layerIndex);	//how many tiles
	int getMapSize();	//how many layers
	string getName();
};


#endif