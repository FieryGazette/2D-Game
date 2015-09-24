#include "Layer.h"

/* Constructor/destructor */
Layer::Layer()
{
}

Layer::Layer(const char* filepath)
{
	this->filepath = filepath;
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
	Tile* ptr = new Tile;
	ptr->xPos = x;
	ptr->yPos = y;

	TileMap.push_back(ptr);
}

void Layer::GetTilePos(int tileIndex, Vector3& pos)
{
	Tile* ptr = TileMap[tileIndex];
	pos.SetXY(ptr->xPos * tileSize, ptr->yPos * tileSize);
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