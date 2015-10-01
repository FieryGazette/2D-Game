#include "Entity.h"
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
vector<Entity*>::iterator it;

/***** constructor / destructor *****/
Entity::Entity()
{
}

Entity::~Entity()
{
	parent = NULL;
}

/****** core ******/
void Entity::Set(string name, Mesh* mesh, Entity* parent)
{
	/* set individual variables */
	this->mesh = mesh;
	this->parent = parent;
	active = true;

	/* Deafult settings */
	position.SetZero();
	scale.Set(1, 1, 1);

	/* update TRS */
	TRS.SetToIdentity();	//trs
	tmp_translation.SetToTranslation(position.x, position.y, position.z);
	tmp_scale.SetToScale(scale.x, scale.y, scale.z);	//scale

	TRS = tmp_translation * tmp_scale;
}

void Entity::AddParent(Entity* parent)
{
	this->parent = parent;
}

void Entity::Init()
{
	if(parent != NULL)
	{
		transformWithParent();	//TRS transform with parent
	}
}


/****** utilities ******/
void Entity::transformWithParent()
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
void Entity::scaleObject(float x, float y, float z)
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

void Entity::scaleObject(float all)
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

void Entity::translateObject(float x, float y, float z)
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

void Entity::translateObject(Vector3 pos)
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

void Entity::rotateObject(float angle, float xAxis, float yAxis, float zAxis)
{
	tmp_rotation.SetToRotation(angle, xAxis, yAxis, zAxis);
	TRS = TRS * tmp_rotation;

	/* position */
	position.SetZero();
	position = TRS * position;
}

void Entity::translate(const Vector3& pos)
{
	Vector3 translatePos = pos - position;
	tmp_translation.SetToTranslation(translatePos.x, translatePos.y, translatePos.z);
	TRS = tmp_translation * TRS;
	
	/* position */
	position = pos;
}

void Entity::translate(float x, float y, float z)
{
	tmp_vec.Set(x, y, z);
	Vector3 translatePos = tmp_vec - position;
	tmp_translation.SetToTranslation(translatePos.x, translatePos.y, translatePos.z);
	TRS = tmp_translation * TRS;
	
	/* position */
	position = tmp_vec;
}

/*** getters ***/
Mesh* Entity::getMesh(){return mesh;}
Vector3 Entity::getScale(){return scale;}
Vector3 Entity::getPosition(){return position;}
Entity* Entity::getParent(){return parent;}
void Entity::setParent(Entity* parent){this->parent = parent;}
Mtx44* Entity::getTRS(){return &TRS;}
void Entity::setActive(bool b){active = b;}
bool Entity::getActive(){return active;}