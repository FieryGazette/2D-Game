#include "Entity.h"
#include "View.h"

/***** constructor / destructor *****/
Entity::Entity()
{
	/*** modifyable data ***/
	mesh = NULL;	//mesh to render (need?)
	scale.SetZero();	//scale
	position.SetZero();	//pos
	active = false;	//active?
}

Entity::~Entity()
{
}

/****** core ******/
void Entity::Set(Mesh* mesh, Vector3 scale, Vector3 position, bool active)
{
	/* set individual variables */
	this->mesh = mesh;
	this->scale = scale;
	this->position = position;
	this->active = active;

}

void Entity::Draw()
{

}

/***** transformation *****/
void Entity::TranslateObject(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Entity::TranslateObject(Vector3 pos)
{
	TranslateObject(pos.x, pos.y, pos.z);
}

void Entity::ScaleObject(float x, float y, float z)
{
	scale.x += x;
	scale.y += y;
	scale.z += z;
}

void Entity::ScaleObject(Vector3 scale)
{
	ScaleObject(scale.x, scale.y, scale.z);
}

void Entity::RotateObject(float x, float y, float z)
{
	angle.x += x;
	angle.y += y;
	angle.z += z;

	if( angle.x < 0.f )
		angle.x = 360 + angle.x;
	else if( angle.x > 360.f )
		angle.x -= 360.f;
	if( angle.y < 0.f )
		angle.y = 360 + angle.x;
	else if( angle.y > 360.f )
		angle.y -= 360.f;
	if( angle.z < 0.f )
		angle.z = 360 + angle.x;
	else if( angle.z > 360.f )
		angle.z -= 360.f;
}

void Entity::Translate(float x, float y, float z)
{
	position.Set(x, y, z);
}

void Entity::Translate(Vector3 pos)
{
	position = pos;
}

void Entity::Scale(float x, float y, float z)
{
	scale.Set(x, y, z);
}

void Entity::Scale(Vector3 scale)
{
	this->scale = scale;
}

void Entity::Rotate(float x, float y, float z)
{
	angle.Set(x, y, z);

	if( angle.x < 0.f )
		angle.x = 360 + angle.x;
	else if( angle.x > 360.f )
		angle.x -= 360.f;
	if( angle.y < 0.f )
		angle.y = 360 + angle.x;
	else if( angle.y > 360.f )
		angle.y -= 360.f;
	if( angle.z < 0.f )
		angle.z = 360 + angle.x;
	else if( angle.z > 360.f )
		angle.z -= 360.f;
}

/*** getters ***/
Vector3 Entity::getScale(){return scale;}
Vector3 Entity::getPosition(){return position;}
void Entity::setActive(bool b){active = b;}
bool Entity::getActive(){return active;}