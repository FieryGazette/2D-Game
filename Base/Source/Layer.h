#ifndef LAYER_H
#define LAYER_H
#include "Character.h"
#include "MeshList.h"
#include "readFrom.h"
#include "writeTo.h"

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
	~Layer();

	/* Re-Create */
	void Set(Geometry::TILE_MAP tileMap, int layer, bool collidable, float tileScale);
	void RecreateLayer(Geometry::TILE_MAP tileMap, int totalX, int totalY);	//clears all tiles and reset again, only way to change tileMap
	bool LoadTileLayer(string& txt);	//update from txt
	
	/* Editing */
	//if is existing tile, will edit that existing tile instead
	void editTile(int& x, int& y, int TileType);
	bool WriteToTxt(string& txt);	//update to txt
	void Clear();	//free memory

	/* Collision */
	bool checkCollision(Character* character);

	/* Getter/setter */
	Geometry::TILE_MAP getTileMap();

	void setLayer(int layer);
	int getLayer();

	void SetCollidable(bool c);
	bool getCollidable();

	void SetTileScale(float s);
	float getTileScale();
private:
	/* Info for map */
	int layer;	//what layer is it
	float tileScale;	//tile scale for this layer
	bool collidable;	//this layer can collide or not
	bool edited;	//is it edited?

	/* Tile stuff */
	vector< vector<int> > TileMap;

	/* tileMap */
	Geometry::TILE_MAP tileMap;	//what tilemap

	static Collision collisionBox;	//Shared collision box
};

#endif