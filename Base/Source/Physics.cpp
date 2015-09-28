#include "Physics.h"

/* Constructor/destructor */
Physics::Physics()
{
	remainingDist = acceleration = vel = 0.f;
	dir.SetZero();
	movement_state = SET_DIR;
}

Physics::~Physics()
{
}

/* Core */
void Physics::Set(float acceleration)
{
	this->acceleration = acceleration;
	movement_state = SET_DIR;
}

/* Movement */
bool Physics::Move(Vector3& pos, const float& max_speed, const Vector3& destination, double dt)
{
	/** Set dir **/
	if( movement_state == SET_DIR )
	{
		if( destination != pos )
			dir = (destination - pos).Normalized();
		movement_state = ACCELERATE;
	}

	/** Accelerate? **/
	else if( movement_state == ACCELERATE )
	{
		if( vel < max_speed )
		{
			vel += acceleration * dt;
			remainingDist += vel;
			pos += dir * vel;

			/* Reach max speed */
			if( vel >= max_speed )
			{
				vel = max_speed;
				movement_state = CONSTANT;
			}
		}
		/** Decelerate **/
		if( shouldDecelerate(pos + dir * vel, destination) )
		{
			pos += (dir * remainingDist) - (destination - pos);
			movement_state = DECELERATE;
			return false;
		}
	}

	if( movement_state == DECELERATE )
	{
		vel -= acceleration * dt;
		pos += dir * vel;
	
		if( vel <= Math::EPSILON )
		{
			vel = 0.f;
			remainingDist = 0.f;
			dir.SetZero();
			pos = destination;
			movement_state = SET_DIR;
			return true;
		}
	}

	return false;
}

bool Physics::shouldDecelerate(const Vector3& pos, const Vector3& destination)
{
	float remaining = (destination - pos).LengthSquared();

	return remainingDist * remainingDist >= remaining;
}