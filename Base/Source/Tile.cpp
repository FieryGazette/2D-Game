#include "Tile.h"
Collision Tile::collisionBox;

/*************************** Tile Class ***************************/
/* Constructor/destructor */
Tile::Tile()
{
}

Tile::~Tile()
{
}

/* Core */
void Tile::Init(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
}

bool Tile::CheckCollision(Collision& checkbox, float tileScale)
{
	/* Set shared collision box to current tile pos */
	collisionBox.SetForTile(xPos, yPos, tileScale);

	/* Check collision with this tile */
	return Collision::CheckCollision(checkbox, collisionBox);
}

/* Utilities*/
bool Tile::operator== (Tile& rhs)
{
	return this->xPos == rhs.xPos && this->yPos == rhs.yPos;
}