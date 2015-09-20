#pragma once
#include <ostream>
#include "Vector3.h"
#include <vector>
using namespace std;

/**
STRICTLY FOR AABB ONLY
store bool for all 6 sides of a cuboid collision box for AABB only
**/
struct Movement_3d
{
	/* For Bound Box */
	enum COLLIDE
	{
		start_X,
		end_X,
		start_Y,
		end_Y, 
		start_Z,
		end_Z,
		UNDEFINED,
	};

	/* constructor destructor */
	COLLIDE collideSide;	//which side collide
	Movement_3d(){collideSide = UNDEFINED;}
	Movement_3d(const Movement_3d& copy){collideSide = copy.collideSide;}
	~Movement_3d(){}

	/* utilities */
	void Reset(){collideSide = UNDEFINED;}

	Movement_3d& operator= (Movement_3d& copy){collideSide = copy.collideSide;return *this;}
	bool operator== (Movement_3d::COLLIDE& check){return collideSide == check;}
};


class Collision2
{
public:
	enum DIRECTION
	{
		TOP_LEFT,
		BOTTOM_LEFT,
		TOP_RIGHT,
		BOTTOM_RIGHT,
		STATIONARY,
	};

	enum TYPE
	{
		BOX,
		SPHERE,
		SLANTED_BOX,
	};

	/* Core */
	//initialize
	void Set(Vector3 pos, Vector3 scale, TYPE type);

	//runtime
	void Start(const Vector3& objectPos, const Vector3& velocity);	//before checking must set up
	void Reset();

	/* Check if collide: */
	//pass in current object's collide box and collide box of object being compared
	static bool CheckCollision(Collision2& current, Collision2& check);

	//1) current type: Sphere --- Check type: Sphere 
	//3) current type: Sphere --- Check type: Slanted Box
	//4) current type: Sphere --- Check type: Box
	//2) current type: Box --- Check type: Box

		/* Sphere (current) to Sphere (check) */
		static bool SphereToSphere(Collision2* current, Collision2* check);

		/* Sphere (current) to Slanted Box (check) */
		static bool SphereToSlantedBox(Collision2* current, Collision2* check);

		/* Sphere (current) to Box (check) */
		static bool SphereToBox(Collision2* current, Collision2* check);

		/* Box (current) to Box (check) */
		static bool BoxToBox(Collision2* current, Collision2* check);

	/* Collision2 response */
	//for respone, set object pos to collision pos
	Collision2();
	~Collision2();


	TYPE type;

	/* Variables for all collision type */
	Vector3 position;
	Vector3 scale;	//if is Sphere, scale.set(radius, radius, radius);

	/* aabb variables */
	Vector3 previousPos;
	DIRECTION direction;

	bool collideX, collideY;
	static Vector3 noSlidePos;
private:

	/* Tangent and Direction */
	void SetTangentAndDir(const Vector3& velocity);	//set tangent and direction
	static void SetToXPos(const float& tangent, const float& xPos, Vector3& currentPos);
	static void SetToYPos(const float& tangent, const float& xPos, Vector3& currentPos);

	/* sliding */
	static vector<Collision2*> slideList;

	static Vector3 originalPos;	//original initial pos
	static Vector3 noCollisionPos;	//final pos if no collision

	/* AABB Detection */
	static bool broadPhrase(Vector3& originalPos, Vector3& finalPos, Vector3& checkPos, Vector3& currentScale, Vector3& checkScale);
	static bool inZone(float& start, float& end, float& checkStart, float& checkEnd);
	static bool checkAABBCollide(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd);

	/* AABB Response */
	static bool CheckAndResponse(Collision2* current, Collision2* check);
	bool isEqual(Vector3& a, Vector3 & b);
};