#ifndef COMPLEX_OBJECT_H
#define COMPLEX_OBJECT_H
#include "Entity.h"
#include "Collision.h"
#include <vector>
#include <string>
using namespace std;

/***********************************************************

Class Complex Object: contains multiple entities and multiple collision boxes

param:
	entityList: vector of entity
	collisionList: vector of collision
	mainPos: main position
***********************************************************/
class ComplexObject
{
public:
	/*** modifyable data ***/
	vector<Entity*> entityList;
	vector<Collision*> collisionList;
	Vector3 mainPos;
public:
	/*** constructor / destructor ***/
	ComplexObject();
	virtual ~ComplexObject();

	/*** core ***/
	void Set(string name);
	virtual void Init();
	virtual void Draw();

	/*** getters setter ***/
	Vector3 getMainPos();
};


#endif