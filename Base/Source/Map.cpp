#include "Map.h"
float Map::offset = 0.1f;
Layer* Map::layer_ptr = NULL;
Vector3 Map::global_vec;

/* Constructor/destructor */
Map::Map(string name)
{
	this->name = name;
}

Map::~Map()
{
}

/* Core */
void Map::AddLayer(bool collidable, float tileScale)
{
	layer_ptr = new Layer;
	layerList.push_back(layer_ptr);
	++totalLayers;

	layerList.back()->Set(Geometry::TILEMAP_NATURE, totalLayers - 1, collidable, tileScale); 
}

bool Map::deleteLayer(int layerNum)
{
	if( layerNum < 0 || layerNum >= totalLayers)
		return false;

	layerList[layerNum]->Clear();
	delete layerList[layerNum];
	layerList.pop_back();
	--totalLayers;
	return true;
}

void Map::RecreateLayer(Geometry::TILE_MAP tileMap, int layer, int totalX, int totalY)
{
	if(layer < 0 || layer >= totalLayers)
		return;

	layerList[layer]->Clear();

	layerList[layer]->RecreateLayer(tileMap, totalX, totalY);
}

void Map::EditLayer(int layerIndex, int tileType, int& x, int& y)
{
	layerList[layerIndex]->editTile(x, y, tileType);
}

void Map::Clear()
{
	for(int i = 0; i < layerList.size(); ++i)
	{
		layerList[i]->Clear();
	}
	layerList.clear();
}

/* Get data */
float Map::getTileSize(int layerIndex)
{
	return 0;
}

int Map::getLayerSize(int layerIndex)	
{
	return 0;
}

int Map::getMapSize()	
{
	return totalLayers;
}

string Map::getName()
{
	return name;
}