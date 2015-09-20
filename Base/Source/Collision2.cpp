#include "Collision2.h"

/* AABB Collision2 */
Vector3 currentStart;	//current collide bound
Vector3 currentEnd;
Vector3 previousStart;	//current collide bound @ previous frame 
Vector3 previousEnd;

Vector3 checkStart, checkEnd;	//start and end for box
Vector3 currentPos;	//current position
float offset = 0.00001f;	//cannot be 0 (or will considered collision even if touching)

float opposite = 0;	//Y
float ajacent = 0;	//X
float tangent = 0;

/* Utility variables */
vector<Collision2*> Collision2::slideList;
Vector3 Collision2::originalPos;	//original initial pos
Vector3 Collision2::noCollisionPos;	//final pos if no collision
Collision2* lastCollided;
Vector3 originalVel;
bool gg = false;
bool y = false;
Vector3 Collision2::noSlidePos;
bool b = false;

Collision2::Collision2()
{
}

/* Init */
void Collision2::Set(Vector3 pos, Vector3 scale, TYPE type)
{
	position = pos;
	previousPos = pos;
	this->scale = scale;
	this->type = type;
	collideX = collideY = false;
}

/* Update */
void Collision2::Start(const Vector3& objectPos, const Vector3& velocity)
{
	if(type == BOX)
	{
		/* Reset variables */
		slideList.clear();
		lastCollided = NULL;
		originalVel = velocity;

		originalPos = previousPos = objectPos;
		noCollisionPos = position = objectPos + velocity;
		
		/* set all collide flags to false */
		collideX = collideY = false;
		
		/* Set tangent and direction */
		SetTangentAndDir(velocity);
		
		b = false;
	}
}

void Collision2::SetTangentAndDir(const Vector3& velocity)
{
	/* Not moving */
	originalVel = velocity;
	
	if(originalVel.IsZero())
	{
		return;
	}
	
	/** Calculate opp, ajacent and tangent **/
	if(velocity.y > 0.f)
	{
		opposite = previousPos.y - position.y;	//Y
		ajacent = position.x - previousPos.x;	//X
	}
	else
	{
		opposite = previousPos.y - position.y;	//Y
		ajacent = position.x - previousPos.x;	//X
	}
	
	tangent = opposite * (1.f / ajacent);

	/** Is ajacent 0 ? **/
	//Yes: opp / 0 == opp
	//No: normal tangent calculation
	gg = false;
	(ajacent >= -Math::EPSILON && ajacent <= Math::EPSILON ) ? gg = true : gg = false;	//Going Full Y
	(opposite >= -Math::EPSILON && opposite <= Math::EPSILON ) ? y = true : y = false;	//going Full X
}

Collision2* a;
Collision2* c;
bool Collision2::CheckCollision(Collision2& current, Collision2& check)
{
	/************ Standardise ************/
	//BOX/SLANTED_BOX must always be current, unless current and check are both SPHERE
	a = &current;
	c = &check;

	/************ Reject ************/
	if(a->type == SLANTED_BOX && c->type == SLANTED_BOX)
		return false;

	else if( (a->type == BOX && c->type == SLANTED_BOX) ||
		(a->type == SLANTED_BOX && c->type == BOX) )
		return false;

	/************ Swap ************/
	//current type: sphere --- check tye: box ===> Swap
	//current type: sphere  --- check tye: slanted_box ===> Swap

	if(a->type == BOX || a->type == SLANTED_BOX)
	{
		if(c->type == SPHERE)
		{
			a = &check;
			c = &current;
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
	if(a->type == SPHERE && c->type == SPHERE)
	{
		return SphereToSphere(a, c);
	}
	else if(a->type == SPHERE && c->type == SLANTED_BOX)
	{
		return SphereToSlantedBox(a, c);
	}
	else if(a->type == SPHERE && c->type == BOX)
	{
		return SphereToBox(a, c);
	}
	else if(a->type == BOX && c->type == BOX)
	{
		return BoxToBox(a, c);
	}

	return false;
}

Collision2::~Collision2()
{

}

/* Sphere (current) to Sphere (check) */
bool Collision2::SphereToSphere(Collision2* current, Collision2* check)
{
	return false;
}

/* Sphere (current) to Slanted Box (check) */
bool Collision2::SphereToSlantedBox(Collision2* current, Collision2* check)
{

	return false;
}

/* Sphere (current) to Box (check) */
bool Collision2::SphereToBox(Collision2* current, Collision2* check)
{
	return false;
}

/** Function Assume Direction is Bottom Right (BR) **/
void Collision2::SetToXPos(const float& tangent, const float& xPos, Vector3& currentPos)
{
	/* get the Y */
	//only ajacent and tangent can be deduced currently
	float ajacent = xPos - currentPos.x;	//X
	float opposite = tangent * ajacent;				//Y
	currentPos.y -= opposite;
	currentPos.x = xPos;
}

void Collision2::SetToYPos(const float& tangent, const float& yPos, Vector3& currentPos)
{
	/* get the X */
	//only ajacent and tangent can be deduced currently
	float opposite = currentPos.y - yPos;				//Y
	float ajacent = opposite * (1.f / tangent);	//X
	currentPos.x += ajacent;
	currentPos.y = yPos;
}

/* Box (current) to Box (check) */
bool Collision2::BoxToBox(Collision2* current, Collision2* check)
{
	/* if not moving, not colliding with anything else */
	if( originalVel.IsZero() )
	{
		return false;
	}
	
	/** Test eligibility for sliding check **/
	if( broadPhrase(originalPos, noCollisionPos, check->position, current->scale, check->scale) ) 
	{
		slideList.push_back(check);
	
		
		/** Test eligibility for collision **/
		if( !broadPhrase(current->previousPos, current->position, check->position, current->scale, check->scale) ) 
		{
			return false;
		}

		if( CheckAndResponse(current, check) )
		{
			lastCollided = check;	//no need check slide with current
			return true;
		}
	}

	return false;
}

float contactX = 0;
float contactY = 0;
float yOffset = 0;
void Collision2::Reset()
{
	//cout <<"X: " << collideX << "  Y: " << collideY << endl;
	previousPos = position;	//set starting pos to current pos

	//if( isEqual(previousPos, noCollisionPos) )
	//{
	//	return;
	//}

	/* Slide check */
	if( !collideX )	//if not collided X, can go all the way
	{
		position.x = noCollisionPos.x;
	}
	else if( !collideY  )	//if not collided Y, can go all the way
	{
		position.y = noCollisionPos.y;
	}

	noSlidePos = previousPos;
	originalVel = position - previousPos;	//remaining vel to travel

	/* RESET tangent and direction */
	SetTangentAndDir(originalVel);	//only do this after previousPos and position done properly
	//b = true;
	//if( direction == STATIONARY)
	//{
	//	return;
	//}
	//
	/* check through if collide with any other boxes in original broadphrase */
	for(int i = 0; i < slideList.size(); ++i)
	{
		if(slideList[i] != lastCollided)
		{
			/** Test eligibility for collision **/
			if( !broadPhrase(previousPos, position, slideList[i]->position, this->scale, slideList[i]->scale) ) 
			{
				continue;
			}

			CheckAndResponse(this, slideList[i]);
		}
	}
}

bool Collision2::isEqual(Vector3& a, Vector3 & b)
{
	return (a.x >= b.x - Math::EPSILON && a.x <= b.x + Math::EPSILON) &&
		(a.y >= b.y - Math::EPSILON && a.y <= b.y + Math::EPSILON) &&
		(a.z >= b.z - Math::EPSILON && a.z <= b.z + Math::EPSILON);
}

Vector3 checkScale_Half;
Vector3 currentScale_Half;
bool Collision2::CheckAndResponse(Collision2* current, Collision2* check)
{
	/* holding variable to store current position (So actual position not modified during checking) */
	currentPos = current->position;	
	
	/* Half scale */
	checkScale_Half = check->scale * 0.5f;
	currentScale_Half = current->scale * 0.5f;

	/* update start and end */
	currentStart = currentPos - currentScale_Half;
	currentEnd = currentPos + currentScale_Half;

	previousStart = current->previousPos - currentScale_Half;
	previousEnd = current->previousPos + currentScale_Half;

	/** checkBox start and end **/
	checkStart = check->position - checkScale_Half;	//set start for box1
	checkEnd = check->position + checkScale_Half;	//set end for box1

	/************************************ Check Collision2 ************************************/
	/** Test 1: check if collide at X side  **/
	/** Test 2: check if collide at Y side **/
	
	//pos just touching X side
	if( gg == false )	//TANGENT == 1: NEVER CONTACT X SIDE
	{
		if(originalVel.x > 0.f)	//if right side
		{
			contactX = check->position.x - (checkScale_Half.x + currentScale_Half.x) - offset;
		}
		else
		{
			contactX = check->position.x + (checkScale_Half.x + currentScale_Half.x) + offset;
		}

		SetToXPos(tangent, contactX, currentPos);	//translate to touch X side
		currentStart = currentPos - currentScale_Half;	//set start for current
		currentEnd = currentPos + currentScale_Half;	//set end for current

		/** once X side is touched, check if y range intersects (current.y intersects check.y) **/
		if(currentEnd.y > checkStart.y && currentStart.y < checkEnd.y)
		{
			current->collideX = current->collideY = false;
			current->position = currentPos;
			current->collideX = true;
			return true;
		}
	}

	/** else, check if can contact at Y start **/
	if( y == false )
	{
		/* translate to just touching top of check box */
		if(originalVel.y > 0.f)	//if right side
		{
			yOffset = -(checkScale_Half.y + currentScale_Half.y + offset);
		}
		else
		{
			yOffset = (checkScale_Half.y + currentScale_Half.y + offset);
		}

		/* contact point Y */
		contactY = check->position.y + yOffset;

		SetToYPos(tangent, contactY, currentPos);
		currentStart = currentPos - currentScale_Half;	//set start for current
		currentEnd = currentPos + currentScale_Half;	//set end for current

		/* translate start and end Y in opp dir of Contact Point Y to see if they intersect */
		currentStart.y -= yOffset;
		currentEnd.y -= yOffset;

		/* check if collide (X and Y) */
		if(checkAABBCollide(currentStart, currentEnd, checkStart, checkEnd))
		{
			current->collideX = current->collideY = false;
			current->position = currentPos;
			current->collideY = true;
			return true;
		}
	}

	/* if no contact, return false */
	return false;
}

bool Collision2::broadPhrase(Vector3& originalPos, Vector3& finalPos, Vector3& checkPos, Vector3& currentScale, Vector3& checkScale)
{
	/************************************ Check if box needs collision check ************************************/
	/* Check if checkBox collides with start-end zone */ 
	/* length and height of zone */
	float length = finalPos.x - originalPos.x;	//x
	float height = finalPos.y - originalPos.y;	//y
	float width = finalPos.z - originalPos.z;	//z
	
	Vector3 startZone, endZone;

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


bool Collision2::inZone(float& start, float& end, float& checkStart, float& checkEnd)
{
	//check x and y only
	return (end > checkStart && start < checkEnd);
}

bool Collision2::checkAABBCollide(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd)
{
	//check x and y only
	return (currentEnd.x > checkStart.x && currentStart.x < checkEnd.x) &&
		(currentEnd.y > checkStart.y && currentStart.y < checkEnd.y);
}
