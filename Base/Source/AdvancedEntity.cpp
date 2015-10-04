#include "AdvancedEntity.h"
#include "View.h"
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
vector<AdvancedEntity*>::iterator it;

/***** constructor / destructor *****/
AdvancedEntity::AdvancedEntity()
{
}

AdvancedEntity::~AdvancedEntity()
{
	parent = NULL;
}

/****** core ******/
void AdvancedEntity::Set(Mesh* mesh, AdvancedEntity* parent)
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

void AdvancedEntity::AddParent(AdvancedEntity* parent)
{
	this->parent = parent;
}

void AdvancedEntity::FinalizeWithParent()
{
	if(parent != NULL)
	{
		transformWithParent();	//TRS transform with parent
	}
}

void AdvancedEntity::Draw()
{

}

/****** utilities ******/
void AdvancedEntity::transformWithParent()
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
void AdvancedEntity::scaleObject(float x, float y, float z)
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

void AdvancedEntity::scaleObject(float all)
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

void AdvancedEntity::translateObject(float x, float y, float z)
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

void AdvancedEntity::translateObject(Vector3 pos)
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

void AdvancedEntity::rotateObject(float angle, float xAxis, float yAxis, float zAxis)
{
	tmp_rotation.SetToRotation(angle, xAxis, yAxis, zAxis);
	TRS = TRS * tmp_rotation;

	/* position */
	position.SetZero();
	position = TRS * position;
}

void AdvancedEntity::translate(const Vector3& pos)
{
	Vector3 translatePos = pos - position;
	tmp_translation.SetToTranslation(translatePos.x, translatePos.y, translatePos.z);
	TRS = tmp_translation * TRS;
	
	/* position */
	position = pos;
}

void AdvancedEntity::translate(float x, float y, float z)
{
	tmp_vec.Set(x, y, z);
	Vector3 translatePos = tmp_vec - position;
	tmp_translation.SetToTranslation(translatePos.x, translatePos.y, translatePos.z);
	TRS = tmp_translation * TRS;
	
	/* position */
	position = tmp_vec;
}

/*** getters ***/
Mesh* AdvancedEntity::getMesh(){return mesh;}
Vector3 AdvancedEntity::getScale(){return scale;}
Vector3 AdvancedEntity::getPosition(){return position;}
AdvancedEntity* AdvancedEntity::getParent(){return parent;}
void AdvancedEntity::setParent(AdvancedEntity* parent){this->parent = parent;}
Mtx44* AdvancedEntity::getTRS(){return &TRS;}
void AdvancedEntity::setActive(bool b){active = b;}
bool AdvancedEntity::getActive(){return active;}