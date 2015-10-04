#ifndef ENTITY_H
#define ENTITY_H
#include "Mesh.h"
#include "MatrixStack.h"
#include "Collision.h"
#include <vector>
#include <string>
using namespace std;

class Entity
{
protected:
	/*** modifyable data ***/
	Mesh* mesh;	//mesh to render (need?)
	Vector3 scale;	//scale
	Vector3 position;	//pos
	Vector3 angle;	//angle for X, Y, Z
	bool active;	//active?

public:
	/*** constructor / destructor ***/
	Entity();
	virtual ~Entity();

	/*** core ***/
	void Set(Mesh* mesh, Vector3 scale, Vector3 position, bool active);	//set basic info

	virtual void Draw();	//render the object

	void TranslateObject(float x, float y, float z);
	void TranslateObject(Vector3 pos);
	void ScaleObject(float x, float y, float z);
	void ScaleObject(Vector3 scale);
	void RotateObject(float x, float y, float z);

	void Translate(float x, float y, float z);
	void Translate(Vector3 pos);
	void Scale(float x, float y, float z);
	void Scale(Vector3 scale);
	void Rotate(float x, float y, float z);

	/*** getters setter ***/
	Vector3 getScale();
	Vector3 getPosition();
	void setActive(bool b);
	bool getActive();
};


#endif