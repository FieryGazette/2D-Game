#ifndef ENTITY_H
#define ENTITY_H
#include "Object.h"
#include "Collision.h"

/*******************************************************/
/*
Complex characters/objects/other game stuff that are complex/consists of more than 1 parts
like a character has a head and 4 limbs and a body


Have 1/multiple parts/meshes, collision bounds
*/
/*******************************************************/
class Entity
{
public:
	/* Constructor/destructor */
	Entity();
	~Entity();

protected:
	/* Physical skeleton */
	Object* objectList;
	int totalObjects;
	
	/* Collison bound */
	Collision* collisionList;
	int totalBounds;

	/* Basic info */
	Vector3 position;
	Vector3 scale;
};

#endif