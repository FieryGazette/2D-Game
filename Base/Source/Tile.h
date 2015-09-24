#ifndef TILE_H
#define TILE_H
#include "Collision.h"

/*****************************************************************/
/*
	Tile object class. Contains X and Y pos 
*/
/*****************************************************************/
class Tile
{
public:
	/* Constructor/destructor */
	Tile();
	~Tile();

	/* Core */
	void Init(int xPos, int yPos);
	bool CheckCollision(Collision& checkbox, float tileScale);	//Collision box of player, NPC etc

	static Collision collisionBox;	//Shared collision box

	int xPos, yPos;	//x and y pos to
};


#endif