#include "Entity.h"

/* Constructor/destructor */
Entity::Entity()
{

}

Entity::~Entity()
{
	/* Physical skeleton */
	delete objectList;
	
	/* Collison bound */
	delete collisionList;
}