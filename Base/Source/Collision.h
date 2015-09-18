#pragma once
#include <ostream>
#include "Vector3.h"
#include <vector>
using namespace std;

class Collision
{
public:
	enum TYPE
	{
		BOX,
		SPHERE,
		SLANTED_BOX,
	};

	/************************************************* Core *************************************************/
	//initialize
	void Set(Vector3 pos, Vector3 scale, TYPE type);

	//runtime
	void Start(const Vector3& objectPos, const Vector3& velocity);	//before checking must set up
	void Reset();

	/************************************************* Collision Functions *************************************************/
	/* Check if collide: */
	//pass in current object's collide box and collide box of object being compared
	static bool CheckCollision(Collision& current, Collision& check);

	//1) current type: Sphere --- Check type: Sphere 
	//3) current type: Sphere --- Check type: Slanted Box
	//4) current type: Sphere --- Check type: Box
	//2) current type: Box --- Check type: Box

		/* Sphere (current) to Sphere (check) */
		static bool SphereToSphere(Collision* current, Collision* check);

		/* Sphere (current) to Slanted Box (check) */
		static bool SphereToSlantedBox(Collision* current, Collision* check);

		/* Sphere (current) to Box (check) */
		static bool SphereToBox(Collision* current, Collision* check);

		/* Box To Box Swept AABB method */
		static bool BoxToBox(Collision* current, Collision* check);
			static float SweptAABB(Collision& current, Collision& check);

	/* Collision response */
	//for respone, set object pos to collision pos
	Collision();
	~Collision();


	/************************************************* Data Members *************************************************/
	TYPE type;

	/* Variables for all collision type */
	Vector3 position;	//bottom left
	Vector3 scale;	//if is Sphere, scale.set(radius, radius, radius);
	Vector3 vel;

private:

	/*********************************************** Temp. Storage *********************************************/
	/* AABB Collision */
	static Vector3 startingPos;	//startingPos
	static Vector3 currentStart;	//current collide bound
	static Vector3 currentEnd;
	static Vector3 normal;	//swept AABB (If not using, remove)
	static Vector3 currentPos;	//current position

	/* Broad phrasing */
	static Vector3 startZone, endZone;	//for broad phrasing (or whatever its called)
	static Vector3 checkStart, checkEnd;	//start and end for box

	/* Timing */
	static float remainingTime;

	/* Sliding */
	static vector<Collision*> slideList;
	static vector<Collision*>::iterator it;
	static Collision* collided_Box;	//box that is being collided, do not check again
	static Vector3 originalVel;
	static Vector3 originalPos;

	/* Misc */
	static float offset;	//cannot be 0 (or will considered collision even if touching)
	static bool xc, yc, zc;

	/** internal functions please ignore (DO NOT CALL FROM OUTSIDE CLASS) **/
	/* AABB Collision */
	static bool broadPhrase(Vector3& originalPos, Vector3& finalPos, Vector3& checkPos, Vector3& currentScale, Vector3& checkScale);
	static bool inZone(float start, float end, float checkStart, float checkEnd);
	static bool checkAABBCollide(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd);
	void ResetAABB();

	static bool CheckAndResponse(bool x, bool y, bool z, Collision& current, vector<Collision*>& checkList);
};