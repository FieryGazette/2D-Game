#ifndef AMMO_H
#define AMMO_H
#include "Object.h"
#include "MeshList.h"

class Ammo : public Object
{
public:
	enum AMMO_TYPE
	{
		PISTOL,
		UZI,
		SHOTGUN,
		GRENADE,
		TOTAL,
	};

	/* Fixed vel */
	const static float PISTOL_SPEED;
	const static float UZI_SPEED;
	const static float SHOTGUN_SPEED;
	const static float GRENADE_SPEED;

	/* physics */
	const static float GRENADE_DECELERATION;

	/* constructor/destructor */
	Ammo();
	~Ammo();

	/* core */
	void Init(AMMO_TYPE type);

	//pass in the relavant info variables and they will be updated
	void Update(vector<Object*>& objectList);
	void Activate(const Vector3& pos, const Vector3& dir);

private:
	AMMO_TYPE type;
	Vector3 vel;

	/* Utilities */
	static bool collide;
	static Object* collidedObject;
};

#endif