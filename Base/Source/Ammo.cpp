#include "Ammo.h"
/* Fixed vel */
const float Ammo::PISTOL_SPEED = 50.f;
const float Ammo::UZI_SPEED = 50.f;
const float Ammo::SHOTGUN_SPEED = 50.f;
const float Ammo::GRENADE_SPEED = 50.f;

/* physics */
const float Ammo::GRENADE_DECELERATION = 5.f;

/* Utilities */
bool Ammo::collide = false;
Object* Ammo::collidedObject = NULL;

/* constructor/destructor */
Ammo::Ammo()
{
	vel.SetZero();
}

Ammo::~Ammo()
{
}

/* core */
void Ammo::Init(AMMO_TYPE type)
{
	this->type = type;
	Set("Bullet", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL);
	translateObject(0, 0, 2);	//z is higer than many other stuff
	scaleObject(50, 50, 50);
	collide = false;
	entity.setActive(false);
}

//pass in the relavant info variables and they will be updated
void Ammo::Update(vector<Object*>& objectList)
{
	/* If collides */
	if( collide )
	{
		//response: zombie loses hp...
		//collidedObject.hitResponse()
		setActive(false);
	}

	/* Check collision */
	StartChecking(vel);

	/* Check collision */
	collide = false;
	for(int i = 0; i < objectList.size(); ++i)
	{
		if( this == objectList[i] || !objectList[i]->getActive() )
			continue;

		if( checkCollision(*objectList[i]) )	//hit something
		{
			//response: zombie dies
			collide = true;
			collidedObject = objectList[i];
		}
	}

	/* Reset */
	collideBox.Reset();

	/* collision response */
	Response(vel);
}

void Ammo::Activate(const Vector3& pos, const Vector3& dir)
{
	//set basics
	setActive(true);
	translate(pos);

	/* Set vel */
	switch( type )
	{
	case PISTOL:
		vel = dir * PISTOL_SPEED;
		break;
	case UZI:
		vel = dir * UZI_SPEED;
		break;
	case SHOTGUN:
		vel = dir * SHOTGUN_SPEED;
		break;
	case GRENADE:
		vel = dir * GRENADE_SPEED;
		break;
	}
}