#ifndef WEAPON_H
#define WEAPON_H
#include "Ammo.h"

class Weapon
{
public:
	enum WEAPON_TYPE
	{
		PISTOL,
		UZI,
		SHOTGUN,
		GRENADE,
		TOTAL,
	};

	/* max ammo */
	const static int MAX_PISTOL = 50;
	const static int MAX_UZI = 50;
	const static int MAX_SHOTGUN = 50;
	const static int MAX_GRENADE = 20;

	/* constructor/destructor */
	Weapon();
	~Weapon();

	/* core */
	void Init(WEAPON_TYPE type);
	static void InitAmmo(vector<Object*>& objectList);	//call this once in Init to update all active ammo

	//pass in the relavant info variables and they will be updated
	bool Update(double dt, const Vector3& currentPos, Vector3& direction, bool fireWeapon);
	static void UpdateAmmos(vector<Object*>& objectList);	//call this once in Update to update all active ammo
	Ammo* FetchAmmo();	//get ammo: Gurantee have ammo

private:
	/* Global */
	static vector<Ammo*> ammoList;

	/* Local */
	WEAPON_TYPE type;
	int ammo;
	double fireRate;
	double fireTimer;
};

#endif