#include "Object.h"
#include "View.h"

/***** constructor / destructor *****/
Object::Object()
{
}

Object::~Object()
{
}

/****** core ******/
void Object::Set(string name, Mesh* mesh, Object* parent)
{
	entity.Set(mesh, parent->getEntity());
	collided = false;
	this->parent = parent;
}


void Object::Init()
{
	if(parent != NULL)
	{
		entity.transformWithParent();	//TRS transform with parent
	}

	/* OP bound box */
	collideBox.Set(entity.getPosition(), entity.getScale(), Collision::BOX);
}

void Object::Draw()
{
	if( entity.getActive() )
	{
		View::RenderMesh(*entity.getTRS(), entity.getMesh(), false);
	}
}

/***** transformation *****/
void Object::scaleObject(float x, float y, float z)
{
	entity.scaleObject(x, y, z);
}

void Object::scaleObject(float all)
{
	entity.scaleObject(all);
}

void Object::translateObject(float x, float y, float z)
{	
	entity.translateObject(x, y, z);
}

void Object::translateObject(Vector3 pos)
{
	entity.translateObject(pos);
}

void Object::rotateObject(float angle, float xAxis, float yAxis, float zAxis)
{
	entity.rotateObject(angle, xAxis, yAxis, zAxis);
}

void Object::translate(const Vector3& pos)
{
	entity.translate(pos);
}

void Object::translate(float x, float y, float z)
{
	entity.translate(x, y, z);
}


/******** OP Collision ********/
void Object::StartChecking(const Vector3& velocity)
{
	/* Set up collision checking */
	collideBox.Start(entity.getPosition(), velocity);
	collided = false;	//set as no collision yet
}

bool Object::checkCollision(Object& checkMe)
{
	bool b = false;
	//THIS object's collideBox, check object collideBox
	b = Collision::CheckCollision(this->collideBox, checkMe.collideBox);

	if(!collided)
		collided = b;
	
	return b;
}

void Object::Response(const Vector3& vel)
{
	/* 2D response: nvr check for Z */
	//this->collideBox.position = this->collideBox.previousPos + finalVel;
	entity.translate(this->collideBox.position);
}

/*** getters ***/
Mesh* Object::getMesh(){return entity.getMesh();}
Vector3 Object::getScale(){return entity.getScale();}
Collision* Object::getBbox(){return &collideBox;}
Vector3 Object::getPosition(){return entity.getPosition();}
Mtx44* Object::getTRS(){return entity.getTRS();}
void Object::setActive(bool b){entity.setActive(b);}
bool Object::getActive(){return entity.getActive();}
AdvancedEntity* Object::getEntity(){return &entity;}