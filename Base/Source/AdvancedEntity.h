#ifndef ADVANCED_ENTITY_H
#define ADVANCED_ENTITY_H

#include "Mesh.h"
#include "MatrixStack.h"
#include "Collision.h"
#include <vector>
#include <string>
using namespace std;

/***********************************************************

Class AdvancedEntity: the physical part of a in-game object
eg. for a car type, entity is its physical form, including relevant data

param:
	Mesh* mesh: mesh to render
	Vector3 scale: scale factor
	Vector3 position: position
	BoundBox bbox: AABB box
	AdvancedEntity* parent: parent object, to transform along with it like herichical modeling, NULL for no parent
	Mtx44 TRS: the entire transformation matrix for this object, which is transformed along with parent if theres one

***********************************************************/
class AdvancedEntity
{
protected:
	/*** modifyable data ***/
	Mesh* mesh;	//mesh to render (need?)
	Vector3 scale;	//scale
	Vector3 position;	//pos
	AdvancedEntity* parent;	
	bool active;	//active?

	/*** NON-modifyable data ***/
	Mtx44 TRS;
public:
	/*** constructor / destructor ***/
	AdvancedEntity();
	virtual ~AdvancedEntity();

	/*** core ***/
	void Set(Mesh* mesh, AdvancedEntity* parent);	//set basic info
	void AddParent(AdvancedEntity* parent);
	void FinalizeWithParent();	//finalize everything: TRS * with parent TRS

	virtual void Draw();	//render the object

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

	/*** getters setter ***/
	Mesh* getMesh();
	Vector3 getScale();
	Vector3 getPosition();
	AdvancedEntity* getParent();
	void setParent(AdvancedEntity* parent);
	Mtx44* getTRS();
	void setActive(bool b);
	bool getActive();
};

#endif