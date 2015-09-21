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
	/* Weapon */
	weapon.Init(Weapon::PISTOL);

	/* Mesh */
	//sprite animation
	sprite = MeshBuilder::GenerateSpriteAnimation("zombie", 8, 8, 1);
	sprite->textureID[0] = LoadTGA("Image//boxhead_zombie.tga");

	//start col, start row, end col, end row
	sprite->init(0.1f, 0, 4, 7, 4, false);

	/* Character */
	object.Set("character", sprite, NULL, false, false);
	object.translateObject(pos);	//start at right side of box (going top left initially)
	object.scaleObject(scale.x, scale.y, scale.z);

	/* Stats */
	this->health = health;
	this->staminia = staminia;
	this->speed = speed;
}

double changeRate = 0.01;
double timer = changeRate;
double changeDirRate = 0.02;
double changeDirTimer = changeDirRate;
int countchange = 0;
bool dirc = false;
void Player::Update(double dt, bool* myKeys, vector<Object*>& objectLists)
{
	/* Character update */
	Character::Update(dt);

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
	////
	
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

	/* Movement and collision check */
	vel *= dt;
	/*translate(800, 800, 1);
	vel.Set(-500, 500, 0);*/
	cout << "Vel: " << vel << endl;
	/* Set up collision */
	object.StartChecking(vel);

	for(int i = 0; i < objectLists.size(); ++i)
	{
		if(&object != objectLists[i])
		{
			if(objectLists[i]->active)
				object.checkCollision2(*objectLists[i]);
		}
	}

	/* Reset */
	object.collideBox.Reset();

	/* collision response */
	object.Response(vel);

	/* Shoot weapon */
	Vector3 dir(0, 1, 0);
	Vector3 pos = object.position;
	pos.y += object.scale.y * 2;
	weapon.Update(dt, pos, dir, myKeys[RELOAD]);
}
