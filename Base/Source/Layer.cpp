#include "Layer.h"

/* Constructor/destructor */
Layer::Layer()
{
	edited = false;
}

Layer::Layer(Geometry::TILE_MAP tileMap)
{
	this->tileMap = tileMap;
}

Layer::~Layer()
{
}

bool Layer::LoadTileLayer()
{
	/* Open file */


	/* Loop through: X */

		/* Loop through: Y */

		/* Add tile to vector */

	return true;
}

void Layer::addTile(int& x, int& y)
{
	Tile* ptr = NULL;

	for(int i = 0; i < TileMap.size(); ++i)
	{
		if( TileMap[i]->xPos == x && TileMap[i]->yPos == y )
		{
			return;
		}
	}

	ptr = new Tile;
	ptr->xPos = x;
	ptr->yPos = y;

	TileMap.push_back(ptr);
}

void Layer::GetTilePos(int tileIndex, Vector3& pos)
{
	pos.SetXY(TileMap[tileIndex]->xPos * tileSize, TileMap[tileIndex]->yPos * tileSize);
}

float Layer::getTileSize()
{
	return tileSize;
}

int Layer::getTotalTiles()
{
	return TileMap.size();
}

void Layer::Clear()
{
	for(int i = 0; i < TileMap.size(); ++i)
	{
		delete TileMap[i];
	}
	TileMap.clear();
}