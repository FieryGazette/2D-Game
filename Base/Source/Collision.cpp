#include "Collision.h"
#include <sstream>

/* AABB Collision */
Vector3 Collision::startingPos;
Vector3 Collision::currentStart;	//current collide bound
Vector3 Collision::currentEnd;
Vector3 Collision::previousStart;	//current collide bound @ previous frame 
Vector3 Collision::previousEnd;

Vector3 Collision::checkStart, Collision::checkEnd;	//start and end for box
Vector3  Collision::normal;
vector<Collision*> Collision::slideList;
vector<Collision*>::iterator Collision::it;

Vector3 Collision::currentPos;	//current position
float Collision::offset = 0.001f;	//cannot be 0 (or will considered collision even if touching)
Vector3 Collision::startZone, Collision::endZone;

Vector3 Collision::slideDist;
Collision* Collision::collided_Box = NULL;

float Collision::remainingTime;

bool Collision::xc, Collision::yc, Collision::zc;

Vector3 originalVel;
int counter;
Vector3 originalPos;

Collision::Collision()
{
	vel.SetZero();
	normal.SetZero();
}

/* Init */
void Collision::Set(Vector3 pos, Vector3 scale, TYPE type)
{
	position = pos;
	this->scale = scale;
	this->type = type;
}

void Collision::SetForTile(int xPos, int yPos, float tileScale)
{
	this->position.Set( static_cast<float>(xPos) * tileScale, static_cast<float>(yPos) * tileScale, position.z);
	this->scale.Set(tileScale, tileScale, tileScale);
}

/* Update */
void Collision::Start(const Vector3& objectPos, const Vector3& velocity)
{
	if(type == BOX)
	{
		counter = 0;
		normal.SetZero();	
		slideList.clear();	
	
		collided_Box = NULL;
		remainingTime = 1.f;

		/* set velocity */
		vel = velocity;
		originalVel = vel;	//store original velocity
		

		slideDist.SetZero();

		/* set pos */
		startingPos = objectPos;
		position = startingPos + vel;
		originalPos = position;

		/* Not moving */
		if(velocity.IsZero())
		{
			return;
		}
	}
}

Collision* a;
Collision* b;
bool Collision::CheckCollision(Collision& current, Collision& check)
{
	/************ Standardise ************/
	//BOX/SLANTED_BOX must always be current, unless current and check are both SPHERE
	a = &current;
	b = &check;

	/************ Reject ************/
	if(a->type == SLANTED_BOX && b->type == SLANTED_BOX)
		return false;

	else if( (a->type == BOX && b->type == SLANTED_BOX) ||
		(a->type == SLANTED_BOX && b->type == BOX) )
		return false;

	/************ Swap ************/
	//current type: sphere --- check tye: box ===> Swap
	//current type: sphere  --- check tye: slanted_box ===> Swap

	if(a->type == BOX || a->type == SLANTED_BOX)
	{
		if(b->type == SPHERE)
		{
			a = &check;
			b = &current;
		}
	}

	/************ Check collide ************/
	//possible combinations:
	//1) current type: Sphere --- Check type: Sphere 
	//3) current type: Sphere --- Check type: Slanted Box
	//4) current type: Sphere --- Check type: Box
	//2) current type: Box --- Check type: Box

	//see current type is what type of collide bound
	//1)
	if(a->type == SPHERE && b->type == SPHERE)
	{
		return SphereToSphere(a, b);
	}
	else if(a->type == SPHERE && b->type == SLANTED_BOX)
	{
		return SphereToSlantedBox(a, b);
	}
	else if(a->type == SPHERE && b->type == BOX)
	{
		return SphereToBox(a, b);
	}
	else if(a->type == BOX && b->type == BOX)
	{
		return SlideResponse(a, b);
	}

	return false;
}

Collision::~Collision()
{

}

/* Sphere (current) to Sphere (check) */
bool Collision::SphereToSphere(Collision* current, Collision* check)
{
	return false;
}

/* Sphere (current) to Slanted Box (check) */
bool Collision::SphereToSlantedBox(Collision* current, Collision* check)
{

	return false;
}

/* Sphere (current) to Box (check) */
bool Collision::SphereToBox(Collision* current, Collision* check)
{
	return false;
}

float Collision::SweptAABB(Collision& current, Collision& check)
{
	/** Get start and end point **/
	currentStart = current.startingPos - current.scale * 0.5f;
	currentEnd = current.startingPos + current.scale * 0.5f;

	checkStart = check.position - check.scale * 0.5f;
	checkEnd = check.position + check.scale * 0.5f;

	bool checkX = false, checkY = false, checkZ = false;

	/* Check eligibility: not 0 vel */
	if(originalVel.x)
		checkX = true;
	if(originalVel.y)
		checkY = true;
	if(originalVel.z)
		checkZ = true;

	/** Get entry and exit length **/
	float xInvEntry = 0.f, xInvExit = 0.f;
	float yInvEntry = 0.f, yInvExit = 0.f;
	float zInvEntry = 0.f, zInvExit = 0.f;
	float xEntry, xExit, yEntry, yExit, zEntry, zExit;
	xEntry = yEntry = zEntry = -std::numeric_limits<float>::max(); //max: assume not collide 
	xExit = yExit = zExit = std::numeric_limits<float>::max(); //min: assume not collide

	//x
	if( checkX )
	{
		if(originalVel.x > 0)
		{
			xInvEntry = checkStart.x - currentEnd.x;
			xInvExit = checkEnd.x - currentStart.x;
		}
		else
		{
			xInvEntry = checkEnd.x - currentStart.x;
			xInvExit = checkStart.x - currentEnd.x;
		}

		//entry/exit time
		xEntry = xInvEntry * (1.f / originalVel.x);
		xExit = xInvExit * (1.f / originalVel.x);
	}

	//y
	if( checkY )
	{
		if( originalVel.y > 0)
		{
			yInvEntry = checkStart.y - currentEnd.y;
			yInvExit = checkEnd.y - currentStart.y;
		}
		else
		{
			yInvEntry = checkEnd.y - currentStart.y;
			yInvExit = checkStart.y - currentEnd.y;
		}

		//entry/exit time
		yEntry = yInvEntry * (1.f / originalVel.y);
		yExit = yInvExit * (1.f / originalVel.y);
	}

	//z
	if( checkZ )
	{
		if( originalVel.z > 0)
		{
			zInvEntry = checkStart.z - currentEnd.z;
			zInvExit = checkEnd.z - currentStart.z;
		}
		else
		{
			zInvEntry = checkEnd.z - currentStart.z;
			zInvExit = checkStart.z - currentEnd.z;
		}

		//entry/exit time
		zEntry = zInvEntry * (1.f / originalVel.z);
		zExit = zInvExit * (1.f / originalVel.z);
	}

	//max
	float entryTime = (xEntry > yEntry) ? xEntry : yEntry;	//compare x, y first
	entryTime = (zEntry > entryTime) ? zEntry : entryTime;	//compare current result with z

	//min
	float exitTime = (xExit < yExit) ? xExit : yExit;	//compare x, y first
	exitTime = (zExit < exitTime) ? zExit : exitTime;	//compare current result with z


	/** Check if collision occurs **/
	if(exitTime < entryTime)
		return 1.0;

	/** set normal **/
	current.normal.SetZero();

	if( xEntry > yEntry && xEntry > zEntry )
	{
		current.normal.x = 1.f;	
	}

	//collided Y side
	else if( yEntry > xEntry && yEntry > zEntry )
	{
		current.normal.y = 1.f;
	}

	//collided Z side
	else if( zEntry > xEntry && zEntry > yEntry )
	{
		current.normal.z = 1.f;
	}

	return entryTime;
}

bool Collision::SlideResponse(Collision* current, Collision* check)
{
	/***** If inside original broad phrase zone, is potential slide collision *****/

	if( originalVel.IsZero() )
		return false;

	/* push back possible obstacles */
	if( broadPhrase(current->startingPos, originalPos, check->position, current->scale, check->scale) )
	{
		slideList.push_back(check);
	}

	/************************************ Check if box needs collision check (BroadPhrase test) ************************************/
	if( !broadPhrase(current->startingPos, current->position, check->position, current->scale, check->scale) )
	{
		return false;
	}

	/************************************ Get velocity ************************************/
	float CollisionTime = SweptAABB(*current, *check);
	
	/* No collision at all */
	if(CollisionTime >= 1.f)
	{
		return false;
	}

	/* collided set to true */
	
	
	/* Theres collision */
	/* Velocity multiply with collisionTime */
	current->vel = originalVel;	//set it to original velocity
	current->vel *= CollisionTime;
	current->position = current->startingPos;
	current->position += current->vel;
	collided_Box = check;

	return true;
}

bool Collision::broadPhrase(Vector3 originalPos, Vector3 finalPos, Vector3 checkPos, Vector3 currentScale, Vector3 checkScale)
{
	/************************************ Check if box needs collision check ************************************/
	/* Check if checkBox collides with start-end zone */ 
	/* length and height of zone */
	float length = finalPos.x - originalPos.x;	//x
	float height = finalPos.y - originalPos.y;	//y
	float width = finalPos.z - originalPos.z;	//z
	
	//x
	if(length > 0)
	{
		startZone.x = originalPos.x - currentScale.x * 0.5f;
		endZone.x = finalPos.x + currentScale.x * 0.5f;
	}
	else
	{
		startZone.x = finalPos.x - currentScale.x * 0.5f;
		endZone.x = originalPos.x + currentScale.x * 0.5f;
	}

	//y
	if(height > 0)
	{
		startZone.y = originalPos.y - currentScale.y * 0.5f;
		endZone.y = finalPos.y + currentScale.y * 0.5f;
	}
	else
	{
		startZone.y = finalPos.y - currentScale.y * 0.5f;
		endZone.y = originalPos.y + currentScale.y * 0.5f;
	}

	//z
	if(width > 0)
	{
		startZone.z = originalPos.z - currentScale.z * 0.5f;
		endZone.z = finalPos.z + currentScale.z * 0.5f;
	}
	else
	{
		startZone.z = finalPos.z - currentScale.z * 0.5f;
		endZone.z = originalPos.z + currentScale.z * 0.5f;
	}

	checkStart = checkPos - checkScale * 0.5f;
	checkEnd = checkPos + checkScale * 0.5f;
	
	/** Check if in X-Y of broad phrase **/
	if(!checkAABBCollide(startZone, endZone, checkStart, checkEnd))	//if checkBox not in start-end zone
	{
		return false;
	}

	return true;
}

void Collision::Reset()
{
	/** Offset **/
	if(originalVel.x != 0.f)
		(originalVel.x > 0.f) ? position.x -= offset : position.x += offset;
	if(originalVel.y != 0.f)
		(originalVel.y > 0.f) ? position.y -= offset : position.y += offset;
	if(originalVel.z != 0.f)
		(originalVel.z > 0.f) ? position.z -= offset : position.z += offset;

	/* Check for 2 other axis after the first one is collided */
	if( !normal.IsZero() && collided_Box != NULL )
	{
		CheckAndResponse(!normal.x, !normal.y, !normal.z, *this, slideList);	//axis #2
		/** Offset **/
	if(originalVel.x != 0.f)
		(originalVel.x > 0.f) ? position.x -= offset : position.x += offset;
	if(originalVel.y != 0.f)
		(originalVel.y > 0.f) ? position.y -= offset : position.y += offset;
	if(originalVel.z != 0.f)
		(originalVel.z > 0.f) ? position.z -= offset : position.z += offset;

		CheckAndResponse(!normal.x, !normal.y, !normal.z, *this, slideList);	  //axis #3
	}

	/** Offset **/
	if(originalVel.x != 0.f)
		(originalVel.x > 0.f) ? position.x -= offset : position.x += offset;
	if(originalVel.y != 0.f)
		(originalVel.y > 0.f) ? position.y -= offset : position.y += offset;
	if(originalVel.z != 0.f)
		(originalVel.z > 0.f) ? position.z -= offset : position.z += offset;
}

bool Collision::CheckAndResponse(bool x, bool y, bool z, Collision& current, vector<Collision*>& checkList)
{
	/* remaining vel to travel */
	originalVel -= current.vel;	//remaining vel
	
	/* See which side collide */
	if( !x )
		originalVel.x = 0.f;
	if( !y )
		originalVel.y = 0.f;
	if( !z )
		originalVel.z = 0.f;

	/** Box that is being collided previous axis **/
	Collision* ptr = NULL;

	/* set starting pos */
	startingPos = current.position;	//set startPos to currentPos so sweptAABB can function
	current.vel = originalVel;
	current.position += originalVel;

	for(it = checkList.begin(); it != checkList.end(); ++it)
	{
		ptr = *it;

		/* BroadPhrase test */
		if( collided_Box == ptr || !broadPhrase(startingPos, current.position, ptr->position, current.scale, ptr->scale) )
		{
			continue;
		}

		/************************************ Get velocity ************************************/
		float CollisionTime = SweptAABB(current, *ptr);

		/* No collision at all */
		if(CollisionTime >= 1.f)
		{
			continue;
		}
		
		/* Velocity multiply with collisionTime */
		current.vel = originalVel;	//set it to remaining velocity
		current.vel *= CollisionTime;

		/* Set position to new vel */
		current.position = startingPos;
		current.position += current.vel;
	}

	return false;
}

bool Collision::checkSlide(Vector3& normall){return true;}

bool Collision::inZone(float start, float end, float checkStart, float checkEnd)
{
	//check x and y only
	return (end > checkStart && start < checkEnd);
}

bool Collision::checkAABBCollide(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd)
{
	return (currentEnd.x > checkStart.x && currentStart.x < checkEnd.x) &&
		(currentEnd.y > checkStart.y && currentStart.y < checkEnd.y) &&
		(currentEnd.z > checkStart.z && currentStart.z < checkEnd.z);
}

bool Collision::QuickAABBDetection2D(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd)
{
	return (currentEnd.x > checkStart.x && currentStart.x < checkEnd.x) &&
		(currentEnd.y > checkStart.y && currentStart.y < checkEnd.y);
}

bool Collision::checkSideCollide(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd, bool x, bool y, bool z)
{
	return false;
}

void Collision::setStartEnd2D(const Vector3& pos, const Vector3& scale, Vector3& start, Vector3& end)
{
	start.Set(pos.x - scale.x * 0.5f, pos.y - scale.y * 0.5f, 0);
	end.Set(pos.x + scale.x * 0.5f, pos.y + scale.y * 0.5f, 0);
}

void Collision::ResetAABB()
{
	//startingPos = position;
}
