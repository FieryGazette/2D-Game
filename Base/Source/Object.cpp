#include "Object.h"
const float OBJECT_DIST_OFFSET = 500.f;
/***** NOTES *****
1) do Angle face with new direction
2) rotate existing object angle will not be updated
3) use something better than define offset for collision dist check
**********/

/***** reusable temp data *****/
Mtx44 tmp_translation;
Mtx44 tmp_rotation;
Mtx44 tmp_scale;
Vector3 tmp_vec(0, 0, 0);
vector<Object*>::iterator it;

/***** constructor / destructor *****/
Object::Object()
{
}

Object::~Object()
{
	parent = NULL;
}

/****** core ******/
void Object::Set(string name, Mesh* mesh, Object* parent, bool light, bool shadow)
{
	/* set individual variables */
	this->mesh = mesh;
	this->parent = parent;
	this->light = light;
	this->shadow = shadow;
	active = true;
	collided = false;

	/* Deafult settings */
	position.SetZero();
	scale.Set(1, 1, 1);

	/* update TRS */
	TRS.SetToIdentity();	//trs
	tmp_translation.SetToTranslation(position.x, position.y, position.z);
	tmp_scale.SetToScale(scale.x, scale.y, scale.z);	//scale

	TRS = tmp_translation * tmp_scale;
}

void Object::AddParent(Object* parent)
{
	this->parent = parent;
}

void Object::Init()
{
	if(parent != NULL)
	{
		transformWithParent();	//TRS transform with parent
	}

	/* OP bound box */
	collideBox.Set(position, scale, Collision2::BOX);
}


/****** utilities ******/
void Object::transformWithParent()
{
	/* translate with parent (reset first) */
	TRS = parent->TRS * TRS;

	/* position */
	position.SetZero();
	position = TRS * position;

	/* scale */
	this->scale.x *= parent->scale.x;
	this->scale.y *= parent->scale.y;
	this->scale.z *= parent->scale.z;
}

/***** transformation *****/
void Object::scaleObject(float x, float y, float z)
{

	scale.x *= x;
	scale.y *= y;
	scale.z *= z;

	tmp_scale.SetToScale(x, y, z);
	TRS = TRS * tmp_scale;

	/* position */
	position.SetZero();
	position = TRS * position;
}

void Object::scaleObject(float all)
{
	scale.x *= all;
	scale.y *= all;
	scale.z *= all;

	tmp_scale.SetToScale(all, all, all);
	TRS = TRS * tmp_scale;

	/* position */
	position.SetZero();
	position = TRS * position;
}

void Object::translateObject(float x, float y, float z)
{	
	tmp_translation.SetToTranslation( x, y, z);

	/* unscale TRS */
	tmp_scale.SetToScale(1.f / scale.x, 1.f / scale.y, 1.f / scale.z);
	TRS = TRS * tmp_scale;
	TRS = TRS * tmp_translation;

	/* scale back TRS */
	tmp_scale.SetToScale(scale.x, scale.y, scale.z);
	TRS = TRS * tmp_scale;

	/* position */
	position.SetZero();
	position = TRS * position;
}

void Object::translateObject(Vector3 pos)
{
	tmp_translation.SetToTranslation(pos.x, pos.y, pos.z);

	/* unscale TRS */
	tmp_scale.SetToScale(1.f / scale.x, 1.f / scale.y, 1.f / scale.z);
	TRS = TRS * tmp_scale;
	TRS = TRS * tmp_translation;

	/* scale back TRS */
	tmp_scale.SetToScale(scale.x, scale.y, scale.z);
	TRS = TRS * tmp_scale;

	/* position */
	position.SetZero();
	position = TRS * position;
}

void Object::rotateObject(float angle, float xAxis, float yAxis, float zAxis)
{
	tmp_rotation.SetToRotation(angle, xAxis, yAxis, zAxis);
	TRS = TRS * tmp_rotation;

	/* position */
	position.SetZero();
	position = TRS * position;
}

void Object::translate(const Vector3& pos)
{
	Vector3 translatePos = pos - position;
	tmp_translation.SetToTranslation(translatePos.x, translatePos.y, translatePos.z);
	TRS = tmp_translation * TRS;
	
	/* position */
	position = pos;
}

void Object::translate(float x, float y, float z)
{
	tmp_vec.Set(x, y, z);
	Vector3 translatePos = tmp_vec - position;
	tmp_translation.SetToTranslation(translatePos.x, translatePos.y, translatePos.z);
	TRS = tmp_translation * TRS;
	
	/* position */
	position = tmp_vec;
	collideBox.position = position;
}

void Object::checkCollision(Object& checkObject)
{
	
}


/******** OP Collision ********/
void Object::StartChecking(const Vector3& velocity)
{
	/* Set up collision checking */
	collideBox.Start(position, velocity);
	collided = false;	//set as no collision yet
}

bool Object::checkCollision2(Object& checkMe)
{
	bool b = false;
	b = Collision2::CheckCollision(this->collideBox, checkMe.collideBox);

	if(!collided)
		collided = b;
	
	return b;
}

void Object::Response(const Vector3& vel)
{
	/* 2D response: nvr check for Z */
	//this->collideBox.position = this->collideBox.previousPos + finalVel;
	//cout << this->collideBox.position + this->collideBox.scale * 0.5f << endl;
	translate(this->collideBox.position + this->collideBox.scale * 0.5f);
}

/*** getters ***/
Mesh* Object::getMesh(){return mesh;}
Vector3 Object::getScale(){return scale;}
Collision2* Object::getBbox(){return &collideBox;}
Vector3 Object::getPosition(){return position;}
Object* Object::getParent(){return parent;}
Mtx44* Object::getTRS(){return &TRS;}
bool Object::getLight(){return light;}
void Object::setActive(bool b){active = b;}
bool Object::getActive(){return active;}
void Object::setShadow(bool s){shadow = s;}
bool Object::getShadow(){return shadow;}