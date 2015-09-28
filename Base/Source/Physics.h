#ifndef PHYSICS_H
#define PHYSICS_H
#include "Vector3.h"
#include <iostream>
using namespace std;

/**/
/*
	Physics stuff and associated variables.
	!!Position and scale are not physics!!

	DO NOT SET ACCELERATION TOO HIGH as frame movement have limitations
*/
/**/
struct Physics
{
public:
	enum MOVEMENT_STATE
	{
		SET_DIR,
		ACCELERATE,
		DECELERATE,
		CONSTANT,
	} movement_state;

	float remainingDist;
	Vector3 dir;
	float vel;
	float acceleration;

	/* Constructor/destructor */
	Physics();
	~Physics();

	/* Core */
	void Set(float acceleration);

	/* Movement */
	//returns true if reached
	bool Move(Vector3& pos, const float& max_speed, const Vector3& destination, double dt); 
	bool shouldDecelerate( const Vector3& pos, const Vector3& destination);
};

#endif