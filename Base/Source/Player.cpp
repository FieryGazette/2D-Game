#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

/* Core */
void Player::Init(Vector3 pos, Vector3 scale, DIRECTION facingDir, float health, float staminia, float speed)
{
	weapon.Init(Weapon::PISTOL);

	Set("character", Geometry::meshList[Geometry::GEO_CUBE_RED], NULL, false, false);
	translateObject(pos);	//start at right side of box (going top left initially)
	scaleObject(scale.x, scale.y, scale.z);

	this->health = health;
	this->staminia = staminia;
	this->speed = speed;
}

void Player::Update(double dt, bool* myKeys, vector<Object*>& objectLists)
{
	/* Controls */
	vel.SetZero();
	if( myKeys[FORWARD] ) 
	{
		vel.y += speed;
	}
	if( myKeys[BACKWARD] )
	{
		vel.y -= speed;
	}
	if( myKeys[LEFT] )
	{
		vel.x -= speed;
	}
	if( myKeys[RIGHT] )
	{
		vel.x += speed;
	}
	
	/* Shoot weapon */
	Vector3 dir(0, 1, 0);
	weapon.Update(dt, position, dir, myKeys[RELOAD]);

	/* Movement and collision check */
	/* Set up collision */
	StartChecking(vel);

	for(int i = 0; i < objectLists.size(); ++i)
	{
		if(this != objectLists[i])
		{
			if(objectLists[i]->active)
				checkCollision2(*objectLists[i]);
		}
	}

	/* Reset */
	collideBox.Reset();

	/* collision response */
	Response(vel);
}

Mesh* Player::getMesh()
{
	return Object::mesh;
}