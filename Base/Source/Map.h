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
	int index;	//index in list

	/* Utilities */
	static float offset;	//offset btw diff layers
	static Layer* layer_ptr;
	static Vector3 global_vec;
public:
	/* Constructor/destructor */
	Map(string name, int index);
	~Map();

	/* Core */
	void AddLayer(bool collidable, float tileScale);
	void RecreateLayer(Geometry::TILE_MAP tileMap, int layer, int totalX, int totalY);	//recreate this layer
	void EditLayer(int layerIndex, int tileType, int& x, int& y);
	bool deleteLayer(int layerNum);
	void Clear();

	/* Get data */
	//pass in which layer, tile index and pos variable
	float getTileSize(int layerIndex);
	int getLayerSize(int layerIndex);	//how many tiles
	int getMapSize();	//how many layers
	string getName();
	int getIndex();
	void setIndex(int i);
};


#endif