#ifndef SUPER_OBJECT_H
#define SUPER_OBJECT_H

#include "Object.h"
#include <vector>
#include <string>
using namespace std;

/***********************************************************

Class Super Object: contains multiple objects

param:
	objectList: vector of objects
	mainPos: main position
***********************************************************/
class SuperObject
{
public:
	/*** modifyable data ***/
	vector<Object*> objectList;
	Vector3 mainPos;
public:
	/*** constructor / destructor ***/
	SuperObject();
	virtual ~SuperObject();

	/*** core ***/
	void Set(string name);
	virtual void Init();
	virtual void Draw();

	/*** getters setter ***/
	Vector3 getMainPos();
};


#endif