#include "Map.h"
float Map::offset = 0.1f;
Layer* Map::layer_ptr = NULL;
Vector3 Map::global_vec;
Tile* Map::tile_ptr = NULL;

/* Constructor/destructor */
Map::Map(string name)
{
	this->name = name;
}

Map::~Map()
{
}

/* Core */
void Map::AddLayer(const char* tileMapPath)
{
	layer_ptr = new Layer(tileMapPath);
	layerList.push_back(layer_ptr);
	++totalLayers;

	/* Load tilemap o this layer */
	layer_ptr->LoadTileLayer();
}

bool Map::deleteLayer(int layerNum)
{
	layerList[layerNum]->Clear();
	delete layerList[layerNum];
	layerList.pop_back();

	return true;
}

void Map::AddTile(int layerIndex, int& x, int& y)
{
	layerList[layerIndex]->addTile(x, y);
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
void Map::GetPosOfTile(int layerIndex, int tileIndex, Vector3& pos)
{
	layerList[layerIndex]->GetTilePos(tileIndex, pos);
}

float Map::getTileSize(int layerIndex)
{
	return layerList[layerIndex]->getTileSize();
}

int Map::getLayerSize(int layerIndex)	
{
	return layerList[layerIndex]->getTotalTiles();
}

int Map::getMapSize()	
{
	return totalLayers;
}

string Map::getName()
{
	return name;
}