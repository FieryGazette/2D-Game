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

double changeRate = 0.01;
double timer = changeRate;
double changeDirRate = 0.3;
double changeDirTimer = changeDirRate;
int countchange = 0;
bool dirc = true;
void Player::Update(double dt, bool* myKeys, vector<Object*>& objectLists)
{
	/* Controls */

	//dir
	if( changeDirTimer < changeDirRate )
		changeDirTimer += dt;
	else
	{
		//if( myKeys[ SHOOT ] )
		{
			changeDirTimer = 0.0;
			dirc = !dirc;
		}
	}

	//keys
	if( timer < changeRate )
		timer += dt;
	else
	{
		timer = 0.0;

		( dirc ) ? ++countchange : --countchange;

		if( dirc && countchange > 3 )
			countchange = 0;
		else if( !dirc && countchange < 0 )
			countchange = 3;
	}
	
	//myKeys[FORWARD] = myKeys[BACKWARD] = myKeys[LEFT] = myKeys[RIGHT] = false;

	//switch( countchange )
	//{
	//case 0:	//top right
	//	myKeys[FORWARD] = myKeys[RIGHT] = true;
	//	break;
	//case 1:	//top left
	//	myKeys[FORWARD] = myKeys[LEFT] = true;
	//	break;
	//case 2:	//bottom left
	//	myKeys[BACKWARD] = myKeys[LEFT] = true;
	//	break;
	//case 3:	//bottom right
	//	myKeys[BACKWARD] = myKeys[RIGHT] = true;
	//	break;
	//}
	
	
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
	//Vector3 dir(0, 1, 0);
	//Vector3 pos = position;
	//pos.y += scale.y * 0.5f;
	//weapon.Update(dt, pos, dir, myKeys[RELOAD]);

	/* Movement and collision check */
	vel *= dt;
	/*translate(800, 800, 1);
	vel.Set(-500, 500, 0);*/
	//cout << "Vel: " << vel << endl;
	/* Set up collision */
	StartChecking(vel);

	for(int i = 0; i < objectLists.size() - 3; ++i)
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