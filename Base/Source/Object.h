#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.h"

/***********************************************************

Class Object: Physical form with collision

param:
	Entity: physical form
	Collision: collision box

***********************************************************/
class Object
{
public:
	/*** modifyable data ***/
	Object* parent;
	Entity entity;
	Collision collideBox;	//collision box
	bool collided;
public:
	/*** constructor / destructor ***/
	Object();
	virtual ~Object();

	/*** core ***/
	void Set(string name, Mesh* mesh, Object* parent);
	void Init();

	/*** utilities ***/
	void transformWithParent();	//position recalculated after transformation

	/*** transformation ***/
	void scaleObject(float x, float y, float z);
	void scaleObject(float all);
	void translateObject(float x, float y, float z);
	void translateObject(Vector3 pos);
	void rotateObject(float angle, float xAxis, float yAxis, float zAxis);
	void translate(const Vector3& pos);
	void translate(float x, float y, float z);


	/******** OP Collision ********/
	void StartChecking(const Vector3& velocity);
	bool checkCollision(Object& checkMe);
	void Response(const Vector3& vel);

	/*** getters setter ***/
	Mesh* getMesh();
	Vector3 getScale();
	Vector3 getPosition();
	Collision* getBbox();
	Entity* getEntity();
	Mtx44* getTRS();
	void setActive(bool b);
	bool getActive();
};


#endif