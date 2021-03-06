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

	/* Core */
	//initialize
	void Set(Vector3 pos, Vector3 scale, TYPE type);
	void SetForTile(int xPos, int yPos, float tileScale);

	//runtime
	void Start(const Vector3& objectPos, const Vector3& velocity);	//before checking must set up
	void Reset();

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
		static bool SlideResponse(Collision* current, Collision* check);
			static float SweptAABB(Collision& current, Collision& check);

	/* Collision response */
	//for respone, set object pos to collision pos
	Collision();
	~Collision();


	TYPE type;

	/* Variables for all collision type */
	Vector3 position;	//bottom left
	Vector3 scale;	//if is Sphere, scale.set(radius, radius, radius);

	static Vector3 normal;	//swept AABB (If not using, remove)

	//!! optimise so not using vel and normal, just one variable (or better, none)
	Vector3 vel;

	/** Free Use **/
	static bool QuickAABBDetection2D(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd);
	static void setStartEnd2D(const Vector3& pos, const Vector3& scale, Vector3& start, Vector3& end);
private:
	/*** Temporary storage variables ***/
	/* AABB Collision */
	static Vector3 startingPos;	//startingPos
	static Vector3 currentStart;	//current collide bound
	static Vector3 currentEnd;
	static Vector3 previousStart;	//current collide bound @ previous frame 
	static Vector3 previousEnd;

	static Vector3 currentPos;	//current position

	/* Broad phrasing */
	static Vector3 startZone, endZone;	//for broad phrasing (or whatever its called)
	static Vector3 checkStart, checkEnd;	//start and end for box

	static float offset;	//cannot be 0 (or will considered collision even if touching)

	static Vector3 slideDist;	//slide dist for sliding AABB

	static float remainingTime;

	static vector<Collision*> slideList;
	static vector<Collision*>::iterator it;
	static Collision* collided_Box;

	static bool xc, yc, zc;

	/** internal functions please ignore (DO NOT CALL FROM OUTSIDE CLASS) **/
	/* AABB Collision */
	static bool broadPhrase(Vector3 originalPos, Vector3 finalPos, Vector3 checkPos, Vector3 currentScale, Vector3 checkScale);
	static bool inZone(float start, float end, float checkStart, float checkEnd);
	static bool checkAABBCollide(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd);
	static bool checkSideCollide(Vector3& currentStart, Vector3& currentEnd, Vector3& checkStart, Vector3& checkEnd, bool x, bool y, bool z);
	bool checkSlide(Vector3& normal);
	void ResetAABB();

	static bool CheckAndResponse(bool x, bool y, bool z, Collision& current, vector<Collision*>& checkList);
};